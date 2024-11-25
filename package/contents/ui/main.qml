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
    toolTipMainText: i18n("This is %1", Plasmoid.title)
    AirpodsHandler {
        id: airpodsHandler
    }
    fullRepresentation: PlasmaExtras.Representation {
        ColumnLayout {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            Kirigami.FormLayout {
                // label: i18n("AirPods")
                Layout.fillWidth: true
                Kirigami.Separator {
                    Kirigami.FormData.isSection: true
                    Kirigami.FormData.label: Plasmoid.title
                }
                ProgressBar {
                    from: 0
                    to: 100
                    value: 50
                    Kirigami.FormData.label: i18n("Battery:")
                }
                ComboBox {
                    id: comboBox
                    model: ["AirPods", "AirPods Pro"]
                    currentIndex: 1
                    Kirigami.FormData.label: i18n("Noise Cancellation:")
                    // Layout.fillWidth: true
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