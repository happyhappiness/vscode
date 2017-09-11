        return port;
      }
#if defined(_WIN32)
      if (WSAGetLastError() != WSAEADDRINUSE) {
        Socket::Error("TryBindHost");
      }
#else
      if (errno != EADDRINUSE) {
        Socket::Error("TryBindHost");
      }
#endif
