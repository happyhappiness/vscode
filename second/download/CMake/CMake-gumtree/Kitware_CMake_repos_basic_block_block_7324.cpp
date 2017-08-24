{
    n = encodeOID((char *) NULL, -1, beg, end);
    if(n >= 0) {
      buf = malloc(n + 1);
      if(buf) {
        encodeOID(buf, n, beg, end);
        buf[n] = '\0';

        if(symbolic) {
          op = searchOID(buf);
          if(op) {
            free(buf);
            buf = strdup(op->textoid);
          }
        }
      }
    }
  }