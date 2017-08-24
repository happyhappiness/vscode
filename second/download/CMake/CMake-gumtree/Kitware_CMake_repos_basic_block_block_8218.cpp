{
    const int stretchedBlockSize = blockSize * (int)stretch;
    const int bytesToAllocate = (int)(
        offsetof(BLOCK, s) + (unsigned)stretchedBlockSize);
    if (bytesToAllocate < 0)
      return 0;

    return (size_t)bytesToAllocate;
  }