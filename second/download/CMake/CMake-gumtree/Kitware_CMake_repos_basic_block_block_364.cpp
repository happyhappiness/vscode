{ /* this means, value was null terminated and not greater than the
         buffer. We have to pad with blanks. Please note that due to memccpy
         logic s points after the terminating null. */
      s--; /* now we point to the terminator. */
      assert(len >= (unsigned int)(s-p));
      if (len > (unsigned int)(s-p))
        memset(s,C_BLANK,len-(unsigned int)(s-p));
    }