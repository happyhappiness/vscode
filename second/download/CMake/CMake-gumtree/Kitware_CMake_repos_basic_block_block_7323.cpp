f(buf) {
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