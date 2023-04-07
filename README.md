[![Build Status](https://travis-ci.org/amc-nu/HesaiLidar_Pandar64_ros.svg?branch=master)](https://travis-ci.org/amc-nu/HesaiLidar_Pandar64_ros)

# HesaiLidar_General_ROS

___
## This is the Pointlaz modified version
 Last modification 2023-01-30 by CASL and Antoine Gruet.

### How to update this version
Since this the pointlaz modifications are contained on a branch, it is possible to isolate the modifications from the update.
- While working on this fork, start by checking out on the master branch
```
git checkout master
```
- Then sync the fork with the update source version by using the method of your choice (see https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/working-with-forks/syncing-a-fork)
- Then checkout back to the Pointlaz branch and merge the updated master into the branch.
```
git checkout Pointlaz
git merge master
git push
```
- It's possible that the merge doesn't complete automatically depending on the complexity of Pointlaz's modifications. In this case, be prepared to do a manual merge. You can use the method of your choice, by example using CLION: check https://www.jetbrains.com/help/clion/resolving-conflicts.html#distributed-version-control-systems

___
## Hesai LiDARs configuration
To operate 2 Hesai LiDARs on the same computer, you will have to configure your Ethernet Ports and internal LiDARs parameters.

### Ethernet Ports and internal LiDARs parameters configuration
Follow the next steps to configure the Ethernet Ports of your computer ([this tutorial](https://www.linuxtechi.com/assign-static-ip-address-ubuntu-20-04-lts/#:~:text=Configuring%20a%20static%20ip%20address,and%20then%20choose%20wired%20settings.&text=In%20the%20next%20window%2C%20Choose,gateway%20and%20DNS%20Server%20IP) has images to help you through the process):
1. Before anything else, on your computer, click on the arrow down at the top right of your screen.
2. Then click on **Settings**. A **Settings** window should open.
3. On the **Settings** window, go to **Network**. You should see all the Ethernet Ports of your computer under **Wired**.
4. Identify (both on your physical computer, and in the **Wired** section) the 2 Ethernet Ports on which you will connect your 2 LiDARs.

#### First LiDAR (lidar_0)
5. Plug your first LiDAR (lidar_0) into its Ethernet Port. You should now see one of your Ethernet Port as **Connected** in the **Wired** section. (You may see a pop window saying *"Connection failed. Activation of network connection failed"*. Do not worry, the Ethernet Ports configuration will fix it.)
6. Click on the "gear" icon of this Ethernet Port. A new window should open.
7. Choose the **IPv4** Tab, then choose **Manual** for **IPv4 Method**.
8. Then, in **Adresses** list, fill the first line with:
   - Address = 192.168.1.100
   - Netmask = 255.255.255.0
   - Gateway = 192.168.1.1
9. Click on **Apply** to save the changes. The window should close.
10. Disable and enable the interface once to assign the IP address to the interface (toggle the purple button).
11. Open Chrome or Firefox, and enter **192.168.1.201** in the URL bar (this is the default IP address of Hesai LiDARs, and will be the final IP address of your first LiDAR lidar_0).
12. The LiDAR web interface should open. Go to the **Settings** tab, and verify that:
    - Under *Control IPv4*, **IPv4 Address = 192.168.1.201**
    - Under *Settings*, **Lidar Destination Port = 2368**
13. If the precedent information are verified, the configuration of your first LiDAR is completed!

#### Second LiDAR (lidar_1)
If the internal IP address of your LiDAR has already been changed, directly go to the **19th step**.  
14. If the internal IP address and Destination Port of your LiDAR have never been changed, it must still be **192.168.1.201** and **2368**. We will have to change it. 
15. Unplug your first LiDAR, and plug your second LiDAR into the same Ethernet port.
16. Open Chrome or Firefox, and enter **192.168.1.201** in the URL bar.
17. The LiDAR web interface should open. Go to the **Settings** tab, and do the next changes:
  - Under *Control IPv4*, **IPv4 Address = 192.168.2.201**
  - Under *Settings*, **Lidar Destination Port = 2369**
18. Click on the **Save** button, and close your web browser.
19. Plug your second LiDAR (lidar_1) into its Ethernet Port. You should now see a second Ethernet Port as **Connected** in the **Wired** section. (You may see a pop window saying *"Connection failed. Activation of network connection failed"*. Do not worry, the Ethernet Ports configuration will fix it.)
20. Click on the "gear" icon of this Ethernet Port. A new window should open. 
21. Choose the **IPv4** Tab, then choose **Manual** for **IPv4 Method**. 
22. Then, in **Adresses** list, fill the first line with:
  - Address = 192.168.2.100
  - Netmask = 255.255.255.0
  - Gateway = 192.168.2.1 
23. Click on **Apply** to save the changes. The window should close. 
24. Disable and enable the interface once to assign the IP address to the interface (toggle the purple button). 
25. Open Chrome or Firefox, and enter **192.168.2.201** in the URL bar (this is the final IP address of your second LiDAR lidar_1). 
26. The LiDAR web interface should open. Go to the **Settings** tab, and verify that:
  - Under *Control IPv4*, **IPv4 Address = 192.168.2.201**
  - Under *Settings*, **Lidar Destination Port = 2369**
27. If the precedent information are verified, the configuration of your second LiDAR is completed!
28. In order to avoid your computer to automatically reset your Ethernet Ports configuration, run this command in a terminal:
```console
  sudo rm /etc/netplan/01-netcfg.yaml
```
*NOTE: It is possible that this file does not exist.*

### Launch files configuration
Even if multiple launch exist in */RosScan/Projects/Hesai_General_ROS/launch*. Only 2 are useful for us:
- **dual_hesai_lidar.launch**: To operate two Hesai LiDARs using ROS.
- **mono_camera.launch**: To operate one Hesai LiDAR using ROS.

No parameters normally need to be tuned, as they are already well configured, but here are the important ones:
- **lidar_0_server_ip**: IP address of the lidar_0. Should be **192.168.1.201**.
- **lidar_1_server_ip**: IP address of the lidar_1. Should be **192.168.2.201**.
- **lidar_0_recv_port**: Destination Port of the lidar_0. Should be **2368**.
- **lidar_1_recv_port**: Destination Port of the lidar_1. Should be **2369**.
- **open_rviz**: If *True*, open Rviz configured to observe the LiDARs data.

___
## About the project
HesaiLidar_General_ROS project includes the ROS Driver for：  
**PandarQT/Pandar64/Pandar40P/Pandar20A/Pandar20B/Pandar40M/PandarXT**  
LiDAR sensor manufactured by Hesai Technology.  

Developed based on [HesaiLidar_General_SDK](https://github.com/HesaiTechnology/HesaiLidar_General_SDK), After launched, the project will monitor UDP packets from Lidar, parse data and publish point clouds frames into ROS under topic: ```/pandar```. It can also be used as an official demo showing how to work with HesaiLidar_General_SDK.

## Environment and Dependencies
**System environment requirement: Linux + ROS**  

　Recommanded:  
　Ubuntu 16.04 - with ROS kinetic desktop-full installed or  
　Ubuntu 18.04 - with ROS melodic desktop-full installed or
  Ubuntu 20.04 - with ROS noetic desktop-full installed 
　Check resources on http://ros.org for installation guide 
 
**Library Dependencies: libpcap-dev + libyaml-cpp-dev**  
```
$sudo apt install libpcap-dev libyaml-cpp-dev
```

## Download and Build

**Install `catkin_tools`**
```
$ sudo apt-get update
$ sudo apt-get install python-catkin-tools
```
**Download code**  
```
$ mkdir -p rosworkspace/src
$ cd rosworkspace/src
$ git clone https://github.com/HesaiTechnology/HesaiLidar_General_ROS.git --recursive
```
**Build**
```
$ cd ..
$ catkin_make -DCMAKE_BUILD_TYPE=Release
```

## Configuration 
```
 $ gedit install/share/hesai_lidar/launch/hesai_lidar.launch
```
**Reciving data from connected Lidar: config lidar ip&port, leave the pcap_file empty**

|Parameter | Default Value|
|---------|---------------|
|server_ip |192.168.1.201|
|lidar_recv_port |2368|
|gps_recv_port  |10110|
|pcap_file ||　　
|multicast_ip ||

Data source will be from connected Lidar when "pcap_file" set to empty, when "multicast_ip" configured, driver will get data packets from multicast ip address. keep "multicast_ip" empty if you are not using multicast, thus driver will monitor the "liar_recv_port" to get data.
Make sure parameters above set to the same with Lidar setting

**Reciving data from pcap file: config pcap_file and correction file path**

|Parameter | Value|
|---------|---------------|
|pcap_file |pcap file path|
|lidar_correction_file |lidar correction file path|　

Data source will be from pcap file once "pcap_file" not empty 

**Reciving data from rosbag: config data_type and publish_type,leave the pcap_file empty**

|Parameter | Value|
|---------|---------------|
|pcap_file ||
|publish_type |points|　
|data_type |rosbag|

Data source will be from rosbag when "pcap_file" is set to empty and "data_type" is set to "rosbag"
Make sure the parameter "publish_type" is set to "points"
Make sure the parameter "namespace" in file hesai_lidar.launch is same with the namespace in rosbag

## Run as independent node

1. Make sure current path in the `rosworkspace` directory
```
$ source devel/setup.bash
```
```
for PandarQT
$ roslaunch hesai_lidar hesai_lidar.launch lidar_type:="PandarQT" frame_id:="PandarQT"
for Pandar64
$ roslaunch hesai_lidar hesai_lidar.launch lidar_type:="Pandar64" frame_id:="Pandar64"
for Pandar20A
$ roslaunch hesai_lidar hesai_lidar.launch lidar_type:="Pandar20A" frame_id:="Pandar20A"
for Pandar20B
$ roslaunch hesai_lidar hesai_lidar.launch lidar_type:="Pandar20B" frame_id:="Pandar20B"
for Pandar40P
$ roslaunch hesai_lidar hesai_lidar.launch lidar_type:="Pandar40P" frame_id:="Pandar40P"
for Pandar40M
$ roslaunch hesai_lidar hesai_lidar.launch lidar_type:="Pandar40M" frame_id:="Pandar40M"
for PandarXT-32
$ roslaunch hesai_lidar hesai_lidar.launch lidar_type:="PandarXT-32" frame_id:="PandarXT-32"
for PandarXT-16
$ roslaunch hesai_lidar hesai_lidar.launch lidar_type:="PandarXT-16" frame_id:="PandarXT-16"
for PandarXTM
$ roslaunch hesai_lidar hesai_lidar.launch lidar_type:="PandarXTM" frame_id:="PandarXTM"
```
2. The driver will publish PointCloud messages to the topic `/pandar`  
3. Open Rviz and add display by topic  
4. Change fixed frame to frame_id to view published point clouds  

## Run as nodelet

1. Make sure current path in the `rosworkspace` directory
```
$ source devel/setup.bash
```
```
for PandarQT
$ roslaunch hesai_lidar cloud_nodelet.launch lidar_type:="PandarQT" frame_id:="PandarQT"
for Pandar64
$ roslaunch hesai_lidar cloud_nodelet.launch lidar_type:="Pandar64" frame_id:="Pandar64"
for Pandar20A
$ roslaunch hesai_lidar cloud_nodelet.launch lidar_type:="Pandar20A" frame_id:="Pandar20A"
for Pandar20B
$ roslaunch hesai_lidar cloud_nodelet.launch lidar_type:="Pandar20B" frame_id:="Pandar20B"
for Pandar40P
$ roslaunch hesai_lidar cloud_nodelet.launch lidar_type:="Pandar40P" frame_id:="Pandar40P"
for Pandar40M
$ roslaunch hesai_lidar cloud_nodelet.launch lidar_type:="Pandar40M" frame_id:="Pandar40M"
for PandarXT-32
$ roslaunch hesai_lidar cloud_nodelet.launch lidar_type:="PandarXT-32" frame_id:="PandarXT-32"
for PandarXT-16
$ roslaunch hesai_lidar cloud_nodelet.launch lidar_type:="PandarXT-16" frame_id:="PandarXT-16"
for PandarXTM
$ roslaunch hesai_lidar cloud_nodelet.launch lidar_type:="PandarXTM" frame_id:="PandarXTM"
```
2. The driver will publish PointCloud messages to the topic `/pandar`  
3. Open Rviz and add display by topic  
4. Change fixed frame to frame_id to view published point clouds  

## Details of launch file parameters and utilities
|Parameter | Default Value|
|---------|---------------|
|pcap_file|Path of the pcap file, once not empty, driver will get data from pcap file instead of a connected Lidar|
|server_ip|The IP address of connected Lidar, will be used to get calibration file|
|lidar_recv_port|The destination port of Lidar, driver will monitor this port to get point clouds packets from Lidar|
|gps_port|The destination port for Lidar GPS packets, driver will monitor this port to get GPS packets from Lidar|
|start_angle|Driver will publish one frame point clouds data when azimuth angle step over start_angle, make sure set to within FOV|
|lidar_type|Lidar module type|
|frame_id|frame id of published messages|
|pcldata_type|0:mixed point clouds data type  1:structured point clouds data type|
|publish_type|default "points":publish point clouds "raw":publish raw UDP packets "both":publish point clouds and UDP packets|
|timestamp_type|default "": use timestamp from Lidar "realtime" use timestamp from the system  driver running on|
|data_type|default "":driver will get point clouds packets from Lidar or PCAP "rosbag":driver will subscribe topic /pandar_packets to get point clouds packets|
|namespace|namesapce of the launching node|
|lidar_correction_file|Path of calibration file, will be used when not able to get calibration file from a connected Liar|
|multicast_ip|The multicast IP address of connected Lidar, will be used to get udp packets from multicast ip address|
|coordinate_correction_flag|default "false":Disable coordinate correction "true":Enable coordinate correction|

