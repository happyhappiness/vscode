    if (ret == -1) {
      int errsv = errno;
      char buf[256];
      Error("Select Error: %s", strerror_r(errsv, buf, sizeof(buf)));      
    }
    return ret;
  }
