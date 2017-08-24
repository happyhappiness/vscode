{
    this->Hostname = "localhost";
#if defined(_WIN32)
    WORD wVersionRequested;
    WSADATA wsaData;
    char name[255];
    wVersionRequested = MAKEWORD(2, 0);
    if (WSAStartup(wVersionRequested, &wsaData) == 0) {
      gethostname(name, sizeof(name));
      WSACleanup();
    }
    this->Hostname = name;
#else
    struct utsname unameInfo;
    int errorFlag = uname(&unameInfo);
    if (errorFlag == 0) {
      this->Hostname = unameInfo.nodename;
    }
#endif
  }