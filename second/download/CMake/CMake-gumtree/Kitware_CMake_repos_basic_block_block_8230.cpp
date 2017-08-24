{
    BLOCK *tem;
    int blockSize = (int)(pool->end - pool->start);
    size_t bytesToAllocate;

    if (blockSize < 0)
      return XML_FALSE;

    if (blockSize < INIT_BLOCK_SIZE)
      blockSize = INIT_BLOCK_SIZE;
    else {
      /* Detect overflow, avoiding _signed_ overflow undefined behavior */
      if ((int)((unsigned)blockSize * 2U) < 0) {
        return XML_FALSE;
      }
      blockSize *= 2;
    }

    bytesToAllocate = poolBytesToAllocateFor(blockSize);
    if (bytesToAllocate == 0)
      return XML_FALSE;

    tem = (BLOCK *)pool->mem->malloc_fcn(bytesToAllocate);
    if (!tem)
      return XML_FALSE;
    tem->size = blockSize;
    tem->next = pool->blocks;
    pool->blocks = tem;
    if (pool->ptr != pool->start)
      memcpy(tem->s, pool->start,
             (pool->ptr - pool->start) * sizeof(XML_Char));
    pool->ptr = tem->s + (pool->ptr - pool->start);
    pool->start = tem->s;
    pool->end = tem->s + blockSize;
  }