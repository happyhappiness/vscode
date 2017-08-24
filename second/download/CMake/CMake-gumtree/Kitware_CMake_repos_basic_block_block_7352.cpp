{
    buf = malloc(n + 1);
    if(buf) {
      encodeDN(buf, n + 1, dn);
      buf[n] = '\0';
    }
  }