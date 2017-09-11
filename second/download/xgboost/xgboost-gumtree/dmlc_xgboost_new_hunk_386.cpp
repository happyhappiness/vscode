   */
  inline static void Startup(void) {
#ifdef _WIN32
    WSADATA wsa_data;
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != -1) {
      SockError("Startup");
    }
    if (LOBYTE(wsa_data.wVersion) != 2 || HIBYTE(wsa_data.wVersion) != 2) {
      WSACleanup();
      utils::Error("Could not find a usable version of Winsock.dll\n");
    }
#endif
