{
    idn2_free(host->encalloc); /* must be freed with idn2_free() since this was
                                 allocated by libidn */
    host->encalloc = NULL;
  }