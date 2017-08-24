r(vmt = p, i = 0; i < rv; i++) {
    obj = vmt2dataptr(vmt, VMT_OBJECT);     /* device */
    stub = vmt2dataptr(vmt, VMT_STUB);      /* mount point */

    if (EQ(obj, dev) || EQ(uv__rawname(obj), dev) || EQ(stub, dev)) {
      uv__free(p);  /* Found a match */
      return 0;
    }
    vmt = (struct vmount *) ((char *) vmt + vmt->vmt_length);
  }