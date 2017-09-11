  /*! \return a string representation of the address */
  inline std::string AddrStr(void) const {
    std::string buf; buf.resize(256);
#ifdef _WIN32
    const char *s = inet_ntop(AF_INET, (PVOID)&addr.sin_addr, &buf[0], buf.length());
#else
	const char *s = inet_ntop(AF_INET, &addr.sin_addr, &buf[0], buf.length());
#endif
    Assert(s != NULL, "cannot decode address");
    return std::string(s);
  }
