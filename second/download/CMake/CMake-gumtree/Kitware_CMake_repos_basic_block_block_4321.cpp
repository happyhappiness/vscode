f(authp->iestyle) {
    tmp = strchr((char *)uripath, '?');
    if(tmp) {
      size_t urilen = tmp - (char *)uripath;
      path = (unsigned char *) aprintf("%.*s", urilen, uripath);
    }
  }