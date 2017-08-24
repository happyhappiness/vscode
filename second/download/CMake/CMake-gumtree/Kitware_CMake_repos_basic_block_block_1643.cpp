{
    /* Copy the arguments into the new command buffer.  */
    kwsysSystem_ptrdiff_t n = pointer_end - pointer_begin;
    memcpy(newCommand, pointer_begin, sizeof(char*) * (size_t)(n));
    newCommand[n] = 0;
  }