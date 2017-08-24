{
    BLOCK *temp;
    int blockSize = (int)((unsigned)(pool->end - pool->start)*2U);
    size_t bytesToAllocate;

    if (blockSize < 0)
      return XML_FALSE;

    bytesToAllocate = poolBytesToAllocateFor(blockSize);
    if (bytesToAllocate == 0)
      return XML_FALSE;

    temp = (BLOCK *)
      pool->mem->realloc_fcn(pool->blocks, (unsigned)bytesToAllocate);
    if (temp == NULL)
      return XML_FALSE;
    pool->blocks = temp;
    pool->blocks->size = blockSize;
    pool->ptr = pool->blocks->s + (pool->ptr - pool->start);
    pool->start = pool->blocks->s;
    pool->end = pool->start + blockSize;
  }