# KDEAirPods

- compile command: cmake -S . -B build -GNinja && cmake --build build --parallel && sudo cmake --install build && sudo rm -rf /usr/lib64/qt6/qml/com && sudo mv /usr/lib64/qml/com /usr/lib64/qt6/qml/ && plasmashell