        return port;
      }
      if (errno != EADDRINUSE) {
        SockError("TryBindHost");
      }
    }
    return -1;
