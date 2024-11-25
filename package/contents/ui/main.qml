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
    Plasmoid.icon: "audio-headphones" //TODO: Change this to airpods icon
    toolTipMainText: i18n("This is %1", Plasmoid.title)
    AirpodsHandler {
        id: airpodsHandler
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
                Button {
                    icon.name: "view-refresh"
                    onClicked: airpodsHandler.updateBatteryStatuses()
                    Layout.alignment: Qt.AlignRight
                }
            }

            Kirigami.Separator {
                Layout.fillWidth: true
            }
            Kirigami.FormLayout {
                Layout.fillWidth: true
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
                visible: airpodsHandler.leftBattery > 0 || airpodsHandler.rightBattery > 0 || airpodsHandler.caseBattery > 0
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
                }
            }
        }
    }
    // compactRepresentation: Item { 
    //     PlasmaComponents3.Label {
    //         text: HelloWorld.text
    //     }
    // }
}