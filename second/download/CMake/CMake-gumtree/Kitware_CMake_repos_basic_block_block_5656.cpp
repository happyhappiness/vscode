{
    failf(data,"WSAStartup failed (%d)",err);
    return CURLE_FAILED_INIT;
  }