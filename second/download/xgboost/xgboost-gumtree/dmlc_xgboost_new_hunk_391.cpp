   *   call this before using the sockets
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
  }
  /*! 
   * \brief shutdown the socket module after use, all sockets need to be closed
   */  
  inline static void Finalize(void) {
    WSACleanup();
  }
  /*! 
   * \brief set this socket to use non-blocking mode
