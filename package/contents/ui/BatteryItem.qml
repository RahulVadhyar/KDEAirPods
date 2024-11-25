import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import org.kde.plasma.core as PlasmaCore
import org.kde.kirigami as Kirigami
import org.kde.plasma.components as PlasmaComponents3

RowLayout{
    
    property int batteryPercentage
    property bool isCharging

    Layout.fillWidth: true
    Layout.alignment: Qt.AlignTop
    PlasmaComponents3.ProgressBar {
        id: chargeBar
        Layout.fillWidth: true
        from: 0
        to: 100
        value: batteryPercentage
    }
    PlasmaComponents3.Label {
        Layout.alignment: Qt.AlignRight
        id: batteryPercentageLabel
        text: i18n("%1%", batteryPercentage)
        textFormat: Text.PlainText
    }

    function getBatteryIconName() {
        if (isCharging) {
            if (batteryPercentage > 80) {
                return "battery-100-charging";
            } else if (batteryPercentage > 60) {
                return "battery-080-charging";
            } else if (batteryPercentage > 40) {
                return "battery-060-charging";
            } else if (batteryPercentage > 20) {
                return "battery-040-charging";
            } else {
                return "battery-020-charging";
            }
        } else {
            if (batteryPercentage > 80) {
                return "battery-100";
            } else if (batteryPercentage > 60) {
                return "battery-080";
            } else if (batteryPercentage > 40) {
                return "battery-060";
            } else if (batteryPercentage > 20) {
                return "battery-040";
            } else {
                return "battery-020";
            }
        }
    }

    Kirigami.Icon {
        source: getBatteryIconName()
        Layout.alignment: Qt.AlignRight
    }
}