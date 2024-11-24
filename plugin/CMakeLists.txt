add_library(KDEAirPodsplugin)
target_link_libraries(KDEAirPodsplugin PRIVATE KF6::I18n Qt6::Gui Qt6::Qml)

install(TARGETS KDEAirPodsplugin DESTINATION ${KDE_INSTALL_QMLDIR}/com/github/rahulvadhyar/private/KDEAirPods)
install(FILES qmldir DESTINATION ${KDE_INSTALL_QMLDIR}/com/github/rahulvadhyar/private/KDEAirPods)
