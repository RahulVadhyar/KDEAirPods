#pragma once

#include <sdbus-c++/sdbus-c++.h>

#include "Event.h"
#include "aap/AapClient.h"
#include "DeviceBattery.h"
#include "DeviceAnc.h"


class Device {
private:
    std::unique_ptr<sdbus::IProxy> _deviceProxy{};

    std::string _name{};
    std::string _address{};
    bool _connected{};
    std::string _modalias{};
    DeviceBattery _battery;
    DeviceAnc _anc{};
    bool isInEar = false;

    Event<bool> _onConnectedPropertyChangedEvent{};

    std::unique_ptr<AapClient> _aapClient{};

    mutable std::mutex _propertyMutex{};

public:
    Device(const sdbus::ObjectPath& objectPath, const std::map<std::string, sdbus::Variant>& deviceInterface);
    // TODO: убрать возможность копирования

    std::string GetName() const {
        std::lock_guard lock{_propertyMutex};
        return _name;
    }

    std::string GetAddress() const {
        std::lock_guard lock{_propertyMutex};
        return _address;
    }

    bool GetConnected() const {
        std::lock_guard lock{_propertyMutex};
        return _connected;
    }
    
    std::string GetModalias() const {
        std::lock_guard lock{_propertyMutex};
        return _modalias;
    }

    bool GetIsInEar() const {
        std::lock_guard lock{_propertyMutex};
        return isInEar;
    }

    std::map<DeviceBatteryType, DeviceBatteryData> GetBatteryStatus() const { // лучше сразу прокидывать Battery
        std::lock_guard lock{_propertyMutex};
        return _battery.GetBatteryStatus();
    }

    DeviceBattery& GetBattery() {
        std::lock_guard lock{_propertyMutex};
        return _battery;
    }

    DeviceAncMode GetAncMode() const { // лучше сразу прокидывать AncStatus
        std::lock_guard lock{_propertyMutex};
        return _anc.GetAncStatus();
    }

    DeviceAnc& GetAnc() {
        std::lock_guard lock{_propertyMutex};
        return _anc;
    }

    Event<bool>& GetConnectedPropertyChangedEvent() {
        return _onConnectedPropertyChangedEvent;
    }

    Event<bool>& GetIsInEarChangedEvent() {
        return _aapClient->GetInEarEvent();
    }

    void Connect(); // TODO: может полностью перейти на Async?
    void ConnectAsync(std::function<void(const sdbus::Error*)>&& callback);

    void Disconnect(); // TODO: может полностью перейти на Async?
    void DisconnectAsync(std::function<void(const sdbus::Error*)>&& callback);

    void SetAnc(DeviceAncMode mode);

private:
    void OnBatteryEvent(const std::map<BatteryType, BatteryWatcherData>& data);
    void OnAncEvent(const AncWatcherData& data);
};
