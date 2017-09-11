  SockAddr(const char *url, int port) {
    this->Set(url, port);
  }
  /*! 
   * \brief set the address
   * \param url the url of the address
   * \param port the port of address
   */
  inline void Set(const char *url, int port) {
    hostent *hp = gethostbyname(url);
    Check(hp != NULL, "cannot obtain address of %s", url);
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    memcpy(&addr.sin_addr, hp->h_addr_list[0], hp->h_length);
  }
  /*! \return a string representation of the address */
  inline std::string ToString(void) const {
    std::string buf; buf.resize(256);
    const char *s = inet_ntop(AF_INET, &addr, &buf[0], buf.length());
    Assert(s != NULL, "cannot decode address");
    std::string res = s;
    sprintf(&buf[0], "%u", ntohs(addr.sin_port));
    res += ":" + buf;
    return res;
  }
};
/*! 
