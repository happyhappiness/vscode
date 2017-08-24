{
    /* buffer was not large enough, reallocate to correct size */
    siz = *(int*)p;
    uv__free(p);
    p = uv__malloc(siz);
    if (p == NULL)
      return -errno;
    rv = mntctl(MCTL_QUERY, siz, (char*)p);
    if (rv < 0)
      return -errno;
  }