#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <string>
#include <vector>
#include <cmath>

#pragma comment(lib, "Ws2_32.lib")

struct LinkedMem {
    UINT32 uiVersion;
    DWORD uiTick;
    float fAvatarPosition[3];
    float fAvatarFront[3];
    float fAvatarTop[3];
    wchar_t name[256];
    float fCameraPosition[3];
    float fCameraFront[3];
    float fCameraTop[3];
    wchar_t identity[256];
    UINT32 context_len;
    unsigned char context[256];
    wchar_t description[2048];
};

LinkedMem* lm = nullptr;

void initMumble() {
    HANDLE hMapObject = OpenFileMappingW(FILE_MAP_ALL_ACCESS, FALSE, L"MumbleLink");
    if (hMapObject == nullptr) {
        std::cout << "Failed to open MumbleLink file mapping\n";
        return;
    }

    lm = (LinkedMem*)MapViewOfFile(hMapObject, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(LinkedMem));
    if (lm == nullptr) {
        std::cout << "Failed to map view of MumbleLink\n";
        CloseHandle(hMapObject);
    }
}

void updateMumble(float x, float y, float z, float yaw, float pitch, const std::string& name, const std::string& context) {
    if (!lm) return;

    if (lm->uiVersion != 2) {
        wcsncpy_s(lm->name, L"Flarial Mumble Link", _TRUNCATE);
        wcsncpy_s(lm->description, L"TestLink is a test of the Link plugin.", _TRUNCATE);
        lm->uiVersion = 2;
    }
    lm->uiTick++;

    float radYaw = (180 - yaw) * (3.1415926535f / 180.0f);
    float radPitch = pitch * (3.1415926535f / 180.0f);

    lm->fAvatarFront[0] = cos(radPitch) * sin(radYaw);
    lm->fAvatarFront[1] = -sin(radPitch);
    lm->fAvatarFront[2] = cos(radPitch) * cos(radYaw);

    lm->fAvatarTop[0] = 0.0f;
    lm->fAvatarTop[1] = 1.0f;
    lm->fAvatarTop[2] = 0.0f;

    lm->fAvatarPosition[0] = x;
    lm->fAvatarPosition[1] = y;
    lm->fAvatarPosition[2] = z;

    lm->fCameraPosition[0] = x;
    lm->fCameraPosition[1] = y;
    lm->fCameraPosition[2] = z;

    lm->fCameraFront[0] = cos(radPitch) * sin(radYaw);
    lm->fCameraFront[1] = sin(radPitch);
    lm->fCameraFront[2] = cos(radPitch) * cos(radYaw);

    lm->fCameraTop[0] = 0.0f;
    lm->fCameraTop[1] = 1.0f;
    lm->fCameraTop[2] = 0.0f;

    int wideSize = MultiByteToWideChar(CP_UTF8, 0, name.c_str(), -1, nullptr, 0);
    if (wideSize > 0) {
        std::vector<wchar_t> wstr(wideSize);
        MultiByteToWideChar(CP_UTF8, 0, name.c_str(), -1, wstr.data(), wideSize);
        wcsncpy_s(lm->identity, wstr.data(), _TRUNCATE);
    }

    size_t bytesToCopy = min(context.size(), size_t(256));
    memcpy(lm->context, context.c_str(), bytesToCopy);
    lm->context_len = static_cast<UINT32>(bytesToCopy);
}

int receiveAll(SOCKET sock, char* buffer, int size) {
    int totalReceived = 0;
    while (totalReceived < size) {
        int bytesReceived = recv(sock, buffer + totalReceived, size - totalReceived, 0);
        if (bytesReceived <= 0) {
            if (bytesReceived == 0) std::cout << "Connection closed by client\n";
            else std::cout << "Receive error: " << WSAGetLastError() << '\n';
            return -1;
        }
        totalReceived += bytesReceived;
    }
    return totalReceived;
}

void handleClient(SOCKET clientSocket) {
    const uint32_t MAX_STRING_LEN = 1024;
    float float1, float2, float3, float4, float5;
    uint32_t len1, len2;
    std::vector<char> str1, str2;

    while (true) {
        //Position
        receiveAll(clientSocket, (char*)&float1, sizeof(float1));
        receiveAll(clientSocket, (char*)&float2, sizeof(float2));
        receiveAll(clientSocket, (char*)&float3, sizeof(float3));

        // rot & pitch
        receiveAll(clientSocket, (char*)&float4, sizeof(float4));
        receiveAll(clientSocket, (char*)&float5, sizeof(float5));

        receiveAll(clientSocket, (char*)&len1, sizeof(len1));
        if (len1 > MAX_STRING_LEN) {
            std::cout << "Received string length too large: " << len1 << '\n';
            break;
        }

        str1.resize(len1 + 1);
        receiveAll(clientSocket, str1.data(), len1) <= 0;
        str1[len1] = '\0';

        receiveAll(clientSocket, (char*)&len2, sizeof(len2));
        if (len2 > MAX_STRING_LEN) {
            std::cout << "Received string length too large: " << len2 << '\n';
            break;
        }

        str2.resize(len2 + 1);
        receiveAll(clientSocket, str2.data(), len2);
        str2[len2] = '\0';

        updateMumble(float1, float2, float3, float4, float5, str1.data(), str2.data());

        char ack = 1;
        if (send(clientSocket, &ack, sizeof(ack), 0) == SOCKET_ERROR) {
            std::cout << "Failed to send acknowledgment. Error: " << WSAGetLastError() << '\n';
            break;
        }
    }

    std::cout << "Client disconnected.\n";
    closesocket(clientSocket);
}

void startServer() {
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    sockaddr_in serverAddr{}, clientAddr{};
    int clientSize = sizeof(clientAddr);

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cout << "WSAStartup failed.\n";
        return;
    }

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cout << "Failed to create socket.\n";
        WSACleanup();
        return;
    }

    int opt = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));

    serverAddr.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
    serverAddr.sin_port = htons(5080);

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cout << "Bind failed. Error: " << WSAGetLastError() << '\n';
        closesocket(serverSocket);
        WSACleanup();
        return;
    }

    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cout << "Listen failed. Error: " << WSAGetLastError() << '\n';
        closesocket(serverSocket);
        WSACleanup();
        return;
    }

    std::cout << "Server listening on port 5080...\n";

    while (true) {
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientSize);
        if (clientSocket == INVALID_SOCKET) {
            std::cout << "Accept failed. Error: " << WSAGetLastError() << '\n';
            continue;
        }

        std::cout << "Client connected.\n";
        initMumble();
        handleClient(clientSocket);
    }

    closesocket(serverSocket);
    WSACleanup();
}

int main() {
    system("CheckNetIsolation.exe LoopbackExempt -a -n=Microsoft.MinecraftUWP_8wekyb3d8bbwe");
    startServer();
    return 0;
}
