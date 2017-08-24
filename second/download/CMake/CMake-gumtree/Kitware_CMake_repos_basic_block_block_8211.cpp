(; n > 0; --n, s++) {
    if (!poolAppendChar(pool, *s))
      return NULL;
  }