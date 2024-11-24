cmake_minimum_required(VERSION 3.22.1)

project(KDEAirPods VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOMOC ON)

find_package(ECM REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(FeatureSummary)


find_package(KF6 REQUIRED COMPONENTS
    Plasma
    I18n
)

find_package(Qt6 CONFIG REQUIRED COMPONENTS
    Qml
    Gui
    Core
)

find_package(sdbus-c++ REQUIRED)

add_subdirectory(plugin)
plasma_install_package(package com.github.rahulvadhyar.KDEAirPods)
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)