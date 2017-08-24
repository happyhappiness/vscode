f(res == 0) {
      /* No more certificates in the bundle. */
      free(certbuf);
      break;
    }