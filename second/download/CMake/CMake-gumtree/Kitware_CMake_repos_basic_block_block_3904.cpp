{
      clone+=3;
      clen-=3;
      /* remove the last segment from the output buffer */
      while(outptr > out) {
        outptr--;
        if(*outptr == '/')
          break;
      }
      *outptr = 0; /* zero-terminate where it stops */
    }