  SockAddr(const char *url, int port) {
    this->Set(url, port);
  }
  inline static std::string GetHostName(void) {
    std::string buf; buf.resize(256);
    utils::Check(gethostname(&buf[0], 256) != -1, "fail to get host name");
    return std::string(buf.c_str());
  }
  /*! 
   * \brief set the address
   * \param url the url of the address
   * \param port the port of address
   */
  inline void Set(const char *host, int port) {
    hostent *hp = gethostbyname(host);
    Check(hp != NULL, "cannot obtain address of %s", host);
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    memcpy(&addr.sin_addr, hp->h_addr_list[0], hp->h_length);
  }
  /*! \brief return port of the address*/
  inline int port(void) const {
    return ntohs(addr.sin_port);
  }
  /*! \return a string representation of the address */
  inline std::string AddrStr(void) const {
    std::string buf; buf.resize(256);
    const char *s = inet_ntop(AF_INET, &addr.sin_addr, &buf[0], buf.length());
    Assert(s != NULL, "cannot decode address");
    return std::string(s);
  }
};
/*! 
