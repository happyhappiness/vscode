{
      *portptr++ = '\0'; /* zero terminate, killing the bracket */
      if(':' != *portptr)
        portptr = NULL; /* no port number available */
    }