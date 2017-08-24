{
      sock[s] = conn->tempsock[i];
      rc |= GETSOCK_WRITESOCK(s++);
    }