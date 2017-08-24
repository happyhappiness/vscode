{
    /* OS X still needs to deallocate some memory.
     * Memory was allocated using the system allocator, so use free() here.
     */
    free(dents);
    dents = NULL;
  }