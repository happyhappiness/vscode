f(nread < 0) {
      failf(data, "read: %s", strerror(errno));
      rc = -1;
    }