add_library(webpanel SHARED webpanel.cpp)
target_include_directories(webpanel PRIVATE "${PROJECT_SOURCE_DIR}/fcitx5-webview/include")
target_link_libraries(webpanel WebviewCandidateWindow Fcitx5::Core)
install(TARGETS webpanel DESTINATION "${FCITX_INSTALL_LIBDIR}/fcitx5")

configure_file(webpanel.conf.in.in webpanel.conf.in @ONLY)
fcitx5_translate_desktop_file(${CMAKE_CURRENT_BINARY_DIR}/webpanel.conf.in webpanel.conf)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/webpanel.conf"
  DESTINATION "${CMAKE_INSTALL_PREFIX}/share/fcitx5/addon"
)
