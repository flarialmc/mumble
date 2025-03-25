# Proximity Chat for Bedrock (FREE!)

This guide will help you set up positional audio in Minecraft (Bedrock) using a custom host application and Mumble Link. Follow these steps carefully to get everything running smoothly.

---

## Prerequisites

Before you begin, ensure you have the following:

- **Operating System:** Windows 10/11  
- **Minecraft Edition:** Windows 10 (Bedrock)  
- **Host Application:** Ensure the host application is running. (Available in the release tab in the future.)  
- **Mumble:** Installed on your system  

---

## Step 1: Launch the Host Application

Run the Flarial Linker Application, from here. If successful, you should see a message like:  
```sh
Server listening on port 5080...
```
![image](https://github.com/user-attachments/assets/3467276b-246d-48a2-8686-1ac22fcbbbda)


---

## Step 2: Enable Loopback Exemption

Open Command Prompt as Administrator and run:
```sh
CheckNetIsolation.exe LoopbackExempt -a -n=Microsoft.MinecraftUWP_8wekyb3d8bbwe
```

---

## Step 3: Create a Mumble Link Server

You can set up a Mumble server using [GuildBit.com](https://guildbit.com). A detailed guide will be added soon.

---

## Step 4: Enable Mumble Link Module in Minecraft

- Open the **Flarial Launcher** and click **Launch**.
- In-game, open the **mod menu** and enable the **Mumble Link module**.
- This will connect you and your friends to the server, enabling positional audio.

---

## Step 5: Enable Link Plugin in Mumble

- Open **Mumble**.
- Navigate to **Settings → Plugins**.
- Enable the **Link Plugin**.
- Click **Apply**.
![image](https://github.com/user-attachments/assets/19b95d09-8f5e-476c-b8d3-8c1c3d94b052)


---

## Important Notes

🚨 **Positional audio will NOT work if:**
- The **Link Plugin** is not enabled in Mumble settings.
- You and your friends are not on the **same Minecraft server**.

Once everything is correctly set up, enjoy immersive positional audio in Minecraft Bedrock Edition! 🎧

