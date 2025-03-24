# Positional Audio Setup Guide for Minecraft with Mumble Link

This guide explains how to set up positional audio in Minecraft (Bedrock) using a custom host application and Mumble Link. Follow the steps below to get everything up and running.

---

## Prerequisites

- **Operating System:** Windows 10/11  
- **Minecraft:** Windows 10 (Bedrock) Edition  
- **Host Application:** Make sure the host application is running. This can be found in the release tab in the future.
- **Mumble:** Installed on your system  

---

## Step 1: Run the Host Application

1. **Launch the Host App**  
   Run the custom host executable. It should display a message like:
   `Server listening on port 5080...`

2. **Enable LoopbackExempt**
  Open a Command Prompt as Administrator, then run:
  `CheckNetIsolation.exe LoopbackExempt -a -n=Microsoft.MinecraftUWP_8wekyb3d8bbwe`

3. **Make your mumble link server**
 This can be done through GuildBit.com
 A full guide will be added soon.

4. **Enable Mumble Link Module** 
 Click launch in Flarial Launcher then open the mod menu in-game, and enable the Mumble Link module.
 This should connect you and your friends to the server and you will now have positonal audio in game

5. **Enable Link Plugin**
 Go to Mumble -> Settings -> Plugins -> Link, enable this

POSITIONAL AUDIO WILL NOT WORK IF YOU DON'T HAVE IT ENABLED IN SETTINGS!
IT WILL NOT WORK IF YOU ARE NOT IN THE SAME SERVER!
