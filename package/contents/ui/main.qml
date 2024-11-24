import QtQuick
import org.kde.plasma.core as PlasmaCore
import org.kde.kirigami as Kirigami
import org.kde.plasma.plasmoid
import org.kde.plasma.components as PlasmaComponents3
import com.github.rahulvadhyar.private.KDEAirPods

PlasmoidItem {
    id: root
    Plasmoid.title: i18n("Hello World")
    toolTipMainText: i18n("This is %1", Plasmoid.title)
    fullRepresentation: Item { 
        PlasmaComponents3.Label {
            text: HelloWorld.text
        }
    }
    compactRepresentation: Item { 
    PlasmaComponents3.Label {
        text: HelloWorld.text
    }
    }
}