{
      size_t urilen = tmp - (char *)uripath;
      path = (unsigned char *) aprintf("%.*s", urilen, uripath);
    }