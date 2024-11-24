#include "DeviceAnc.h"

#include "Logger.h"

void DeviceAnc::ClearAnc(){
    _mode = DeviceAncMode::NotAvailable;
}

void DeviceAnc::UpdateFromAppleAnc(AncMode aapMode){
    DeviceAncMode mode = DeviceAnc::AncModeToDeviceAncMode(aapMode);
    LOG_RELEASE("Trying update anc mode %u -> %u", static_cast<unsigned char>(_mode), static_cast<unsigned char>(mode));
    if (mode != _mode){
        _mode = mode;
        LOG_RELEASE("Updated anc mode: %u",  static_cast<unsigned char>(_mode));
        _modeChanged.FireEvent(_mode);
    }
}

DeviceAncMode DeviceAnc::AncModeToDeviceAncMode(AncMode aapMode){
    DeviceAncMode mode;
    switch (aapMode)
    {
        case AncMode::Off:
            mode = DeviceAncMode::Off;
            break;        
        case AncMode::Tra:
            mode = DeviceAncMode::Tra;
            break;    
        case AncMode::On:
            mode = DeviceAncMode::On;
            break;    
        default:
            mode= DeviceAncMode::NotAvailable;
            break;
    }
    
    return mode;
}

AncMode DeviceAnc::DeviceAncModeAncModeTo(DeviceAncMode mode){
    AncMode aapMode;
    switch (mode)
    {
        case DeviceAncMode::Off:
            aapMode = AncMode::Off;
            break;        
        case DeviceAncMode::Tra:
            aapMode = AncMode::Tra;
            break;    
        case DeviceAncMode::On:
            aapMode = AncMode::On;
            break;    
        default:
            aapMode = AncMode::Off;
            break;
    }
    
    return aapMode;
}