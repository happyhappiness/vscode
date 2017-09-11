        return port;
      }
      if (errno != EADDRINUSE) {
        SockError("TryBindHost", errno);
      }
    }
    return -1;
