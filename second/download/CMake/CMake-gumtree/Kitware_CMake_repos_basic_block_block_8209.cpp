{
  do {
    if (!poolAppendChar(pool, *s))
      return NULL;
  } while (*s++);
  s = pool->start;
  poolFinish(pool);
  return s;
}