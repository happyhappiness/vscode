{
      failf(data, "read: %s", strerror(errno));
      rc = -1;
    }