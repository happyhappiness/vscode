{
  if (!poolAppend(pool, enc, ptr, end))
    return NULL;
  if (pool->ptr == pool->end && !poolGrow(pool))
    return NULL;
  *(pool->ptr)++ = 0;
  return pool->start;
}