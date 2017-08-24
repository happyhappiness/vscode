){
  int rv, i = 2;
  struct vmount *p;
  int size_multiplier = 10;
  size_t siz = sizeof(struct vmount)*size_multiplier;
  struct vmount *vmt;
  const char *dev = "/aha";
  char *obj, *stub;

  p = uv__malloc(siz);
  if (p == NULL)
    return -errno;

  /* Retrieve all mounted filesystems */
  rv = mntctl(MCTL_QUERY, siz, (char*)p);
  if (rv < 0)
    return -errno;
  if (rv == 0) {
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

  /* Look for dev in filesystems mount info */
  for(vmt = p, i = 0; i < rv; i++) {
    obj = vmt2dataptr(vmt, VMT_OBJECT);     /* device */
    stub = vmt2dataptr(vmt, VMT_STUB);      /* mount point */

    if (EQ(obj, dev) || EQ(uv__rawname(obj), dev) || EQ(stub, dev)) {
      uv__free(p);  /* Found a match */
      return 0;
    }
    vmt = (struct vmount *) ((char *) vmt + vmt->vmt_length);
  }

  /* /aha is required for monitoring filesystem changes */
  return -1;
}