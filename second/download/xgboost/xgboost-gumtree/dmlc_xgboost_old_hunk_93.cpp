    }
  };
  /*! \brief translate errno to return type */
  inline static ReturnType Errno2Return(int errsv) {
    if (errsv == EAGAIN || errsv == EWOULDBLOCK) return kSuccess;
    if (errsv == ECONNRESET) return kConnReset;
    return kSockError;
  }
