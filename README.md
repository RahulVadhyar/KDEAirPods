# KDEAirPods

This is a KDE plasmoid that shows the battery status of your AirPods. 

Note: This is very alpha and only tested with AirPods 2nd gen. It might cause plasmashell to crash

## Features
- Shows battery status of AirPods
- Shows battery status of AirPods case
- Toolbar status icon
- icon changes based on whether the AirPods are inside the case or not
- Shows charging status
- Shows battery percentage
- Switch between noise cancellation and transparency mode
- Shows the current mode

## To install on fedora:
```bash
cmake -S . -B build -GNinja 
cmake --build build --parallel
sudo cmake --install build 
```

Restart plasmashell after this
<!-- # sudo rm -rf /usr/lib64/qt6/qml/com  -->
<!-- # sudo mv /usr/lib64/qml/com /usr/lib64/qt6/qml/  -->
<!-- # plasmashell -->
## Sources for icons:
airpods with case : https://www.svgrepo.com/svg/533061/airpods

airpods:https://www.svgrepo.com/svg/533058/airpods-alt