import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import org.kde.plasma.core as PlasmaCore
import org.kde.kirigami as Kirigami
import org.kde.plasma.plasmoid
import org.kde.plasma.components as PlasmaComponents3
import org.kde.plasma.extras as PlasmaExtras
import com.github.rahulvadhyar.private.KDEAirPods

PlasmoidItem {
    id: root
    Plasmoid.title: airpodsHandler.deviceName
    Plasmoid.icon: airpodsHandler.connected ? (isAirpodsCharging() ? Qt.resolvedUrl("../icons/airpods-with-case.svg") : Qt.resolvedUrl("../icons/airpods-only.svg")) : Qt.resolvedUrl("../icons/airpods-case-only.svg") 
    toolTipMainText: i18n(Plasmoid.title)
    toolTipSubText: airpodsHandler.connected ? i18n("Connected"  + "\n" + "Left: %1%\nRight: %2%\nCase: %3%", airpodsHandler.leftBattery, airpodsHandler.rightBattery, airpodsHandler.caseBattery) : i18n("Not connected")
    //uncomment this line to hide the plasmoid when airpods are not connected
    // Plasmoid.status: airpodsHandler.connected ? PlasmaCore.Types.ActiveStatus : PlasmaCore.Types.HiddenStatus
    AirpodsHandler {
        id: airpodsHandler
    }

    function isAirpodsCharging() {
        return airpodsHandler.leftCharging || airpodsHandler.rightCharging
    }

    compactRepresentation: MouseArea {
        Layout.minimumWidth: airpodsHandler.connected && !isAirpodsCharging ? Kirigami.Units.gridUnit * 4 : Kirigami.Units.gridUnit * 2
        function getBatteryIconName() {
            if (airpodsHandler.leftCharging && airpodsHandler.rightCharging) {
                if (Math.min(airpodsHandler.leftBattery, airpodsHandler.rightBattery) > 80) {
                    return "battery-100-charging";
                } else if (Math.min(airpodsHandler.leftBattery, airpodsHandler.rightBattery) > 60) {
                    return "battery-080-charging";
                } else if (Math.min(airpodsHandler.leftBattery, airpodsHandler.rightBattery) > 40) {
                    return "battery-060-charging";
                } else if (Math.min(airpodsHandler.leftBattery, airpodsHandler.rightBattery) > 20) {
                    return "battery-040-charging";
                } else {
                    return "battery-020-charging";
                }
            } else {
                if (Math.min(airpodsHandler.leftBattery, airpodsHandler.rightBattery) > 80) {
                    return "battery-100";
                } else if (Math.min(airpodsHandler.leftBattery, airpodsHandler.rightBattery) > 60) {
                    return "battery-080";
                } else if (Math.min(airpodsHandler.leftBattery, airpodsHandler.rightBattery) > 40) {
                    return "battery-060";
                } else if (Math.min(airpodsHandler.leftBattery, airpodsHandler.rightBattery) > 20) {
                    return "battery-040";
                } else {
                    return "battery-020";
                }
            }
        }
        RowLayout{
            visible: airpodsHandler.connected && !isAirpodsCharging()
            anchors.fill: parent
            PlasmaComponents3.Label {
                id: batteryPercentageLabel
                text: i18n("%1%", Math.min(airpodsHandler.leftBattery, airpodsHandler.rightBattery))
                textFormat: Text.PlainText
            }
            Kirigami.Icon {
                source: getBatteryIconName()
            }
        }

        Kirigami.Icon {
            visible: !airpodsHandler.connected || isAirpodsCharging()
            source: Plasmoid.icon
        }
        onClicked: {
            root.expanded = !root.expanded
        }
    }

    fullRepresentation: PlasmaExtras.Representation {
        ColumnLayout {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: Kirigami.Units.largeSpacing
            RowLayout{
                Layout.fillWidth: true
                Kirigami.Heading {
                    Layout.fillWidth: true
                    text: Plasmoid.title
                    level: 1
                    Layout.alignment: Qt.AlignLeft
                }
                Button{
                    text: airpodsHandler.connected ? i18n("Disconnect") : i18n("Connect")
                    onClicked: airpodsHandler.connected ? airpodsHandler.disconnect() : airpodsHandler.connect()
                    Layout.alignment: Qt.AlignRight
                    height: Kirigami.Units.gridUnit
                }
                Button {
                    id: refreshButton
                    icon.name: "view-refresh"
                    onClicked: airpodsHandler.updateBatteryStatuses()
                    Layout.alignment: Qt.AlignRight
                    height: Kirigami.Units.gridUnit
                }
            }

            Kirigami.Separator {
                Layout.fillWidth: true
            }
            Kirigami.FormLayout {
                Layout.fillWidth: true
                visible: airpodsHandler.connected
                BatteryItem {
                    batteryPercentage: airpodsHandler.caseBattery
                    isCharging: airpodsHandler.caseCharging
                    Kirigami.FormData.label: "Case: "
                    visible: airpodsHandler.caseBattery > 0
                }
                BatteryItem {
                    batteryPercentage: airpodsHandler.leftBattery
                    isCharging: airpodsHandler.leftCharging
                    Kirigami.FormData.label: "Left: "
                    visible: airpodsHandler.leftBattery > 0
                }
                BatteryItem {
                    batteryPercentage: airpodsHandler.rightBattery
                    isCharging: airpodsHandler.rightCharging
                    Kirigami.FormData.label: "Right: "
                    visible: airpodsHandler.rightBattery > 0
                }
            }
            Kirigami.Separator {
                Layout.fillWidth: true
                visible: airpodsHandler.connected
            }
            Kirigami.FormLayout {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignBottom
                ComboBox {
                    id: comboBox
                    model: ["Off", "Transparency", "Noise Cancellation"]
                    currentIndex: airpodsHandler.ancStatus - 1
                    Kirigami.FormData.label: i18n("Noise Cancellation:")
                    onCurrentIndexChanged: {
                        airpodsHandler.ancStatus = comboBox.currentIndex + 1
                    }
                    visible: airpodsHandler.connected
                }
                Kirigami.Heading {
                    Layout.fillWidth: true
                    text: airpodsHandler.deviceAddress
                    level: 5
                    Layout.alignment: Qt.AlignLeft
                    Kirigami.FormData.label: i18n("Device Address:")
                }
                Kirigami.Heading {
                    Layout.fillWidth: true
                    text: airpodsHandler.connected ? i18n("Connected") : i18n("Not connected")
                    level: 5
                    Layout.alignment: Qt.AlignLeft
                    Kirigami.FormData.label: i18n("Connection Status:")
                }
            }
        }
    }
}