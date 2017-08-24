(*s) {
    if (!poolAppendChar(pool, *s))
      return NULL;
    s++;
  }