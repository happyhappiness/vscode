do {
    if (!poolAppendChar(pool, *s))
      return NULL;
  } while (*s++);