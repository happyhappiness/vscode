{
    free(socksproxy);  /* Don't bother with an empty socks proxy string or if
                          the protocol doesn't work with network */
    socksproxy = NULL;
  }