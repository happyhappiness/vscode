{
    /* append algorithm */
    tmp = aprintf("%s, algorithm=\"%s\"", *allocuserpwd, d->algorithm);
    if(!tmp)
      return CURLE_OUT_OF_MEMORY;
    free(*allocuserpwd);
    *allocuserpwd = tmp;
  }