cmake_minimum_required(VERSION 3.22.1)

project(KDEAirPods VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOMOC ON)
find_package(ECM REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(FeatureSummary)
include(ECMQmlModule)


find_package(KF6 REQUIRED COMPONENTS
    I18n
)

find_package(Qt6 CONFIG REQUIRED COMPONENTS
    Qml
    Gui
    Core
)
find_package(Plasma REQUIRED)

find_package(sdbus-c++ REQUIRED)

add_compile_options(-fexceptions)
ecm_add_qml_module(KDEAirPodsplugin URI com.github.rahulvadhyar.private.KDEAirPods)
target_sources(KDEAirPodsplugin PRIVATE plugin/KDEAirPods.cpp plugin/airpodsHandler.cpp plugin/batteryStatus.cpp)
target_include_directories(KDEAirPodsplugin PRIVATE plugin/backend)
target_link_libraries(KDEAirPodsplugin PRIVATE KF6::I18n Qt6::Gui Qt6::Qml)
add_subdirectory(plugin/backend)
ecm_finalize_qml_module(KDEAirPodsplugin)


# add_subdirectory(plugin/backend)
plasma_install_package(package com.github.rahulvadhyar.KDEAirPods)
install(TARGETS KDEAirPodsplugin ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)