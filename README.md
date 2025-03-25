# 🎙️ Proximity Chat for Minecraft: Bedrock Edition (FREE!) :video_game:

This guide will help you set up Proximity Chat in Minecraft (Bedrock) using Flarial and Mumble Link. Follow these steps carefully to get everything running smoothly. :white_check_mark:

---

## ⚙️ Prerequisites

Before you begin, ensure you have the following:

- **🖥️ Operating System:** Windows 10/11  
- **:video_game: Minecraft Edition:** Windows 10 (Bedrock)  
- **:satellite: Host Application:** Ensure the host application is running. (Available in the release tab in the future.)  
- **:speaking_head: Mumble:** Installed on your system  

---

## 🚀 Step 1: Launch the Host Application

Run the [Flarial Mumble Link](https://github.com/flarialmc/mumble/releases/download/1.0.0/MumbleLink.exe). If successful, you should see a message like:  
```sh
Server listening on port 5080...
```
![image](https://github.com/user-attachments/assets/3467276b-246d-48a2-8686-1ac22fcbbbda)

---

## 🔄 Step 2: Enable Loopback Exemption

Open Command Prompt as Administrator and run:
```sh
CheckNetIsolation.exe LoopbackExempt -a -n=Microsoft.MinecraftUWP_8wekyb3d8bbwe
```

---

## 🌐 Step 3: Create a Mumble Link Server

You can set up a Mumble server using [GuildBit.com](https://guildbit.com). A detailed guide will be added soon. :pencil:

---

## 🎛️ Step 4: Enable Mumble Link Module in Minecraft

- Open the **Flarial Launcher** and click **Launch**. :arrow_forward:
- In-game, open the **mod menu** and enable the **Mumble Link module**. :level_slider:
- This will connect you and your friends to the server, enabling positional audio. :loud_sound:

---

## 🔌 Step 5: Enable Link Plugin in Mumble

- Open **Mumble**. :microphone:
- Navigate to **Settings → Plugins**. :gear:
- Enab;e **Link to Game and Transmit Position** :white_check_mark:
- Enable the **Link Plugin**. :white_check_mark:
![image](https://github.com/user-attachments/assets/a71bc745-83a3-4069-bdc1-87fd9bef9e70)


---

## 🎧 Best Mumble Settings

To enhance your positional audio experience, adjust the following settings in Mumble:

### :one: Set Transmit Mode to Continuous :arrows_counterclockwise:
Using **Continuous** transmission ensures your voice is always sent without delay. :hourglass_flowing_sand:
![Transmit Mode](https://github.com/user-attachments/assets/e9fd58ae-985c-40f8-8a00-e293939e0ca0)

### :two: Enable the "Headphones" Option :headphones:
This improves spatial audio accuracy, making the experience more immersive. :earth_africa:

### :three: Adjust Maximum Distance to 50 Metres :straight_ruler:
By default, voices may sound too distant. Increase the **Maximum distance** to **50 metres** for a more natural audio experience. :loud_sound:
![Maximum Distance](https://github.com/user-attachments/assets/b5503a5e-793f-4053-8929-ef0e98e6b953)

---

## ⚠️ Important Notes

:rotating_light: **Positional audio will NOT work if:**
- The **Link Plugin** is not enabled in Mumble settings. :x:
- You and your friends are not on the **same Minecraft server**. :globe_with_meridians:
- You don't have positional audio enabled in Mumble's Settings. :x:

Once everything is correctly set up, enjoy immersive positional audio in Minecraft Bedrock Edition! :video_game::headphones::fire:

