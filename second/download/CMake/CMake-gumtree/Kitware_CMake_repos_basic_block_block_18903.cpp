{
  uv__dirent_t **dents;
  int n;

  dents = NULL;
  n = scandir(req->path, &dents, uv__fs_scandir_filter, uv__fs_scandir_sort);

  /* NOTE: We will use nbufs as an index field */
  req->nbufs = 0;

  if (n == 0) {
    /* OS X still needs to deallocate some memory.
     * Memory was allocated using the system allocator, so use free() here.
     */
    free(dents);
    dents = NULL;
  } else if (n == -1) {
    return n;
  }

  req->ptr = dents;

  return n;
}