{
  z_stream *z = &k->z;          /* zlib state structure */

  /* Initialize zlib? */
  if(k->zlib_init == ZLIB_UNINIT) {
    memset(z, 0, sizeof(z_stream));
    z->zalloc = (alloc_func)zalloc_cb;
    z->zfree = (free_func)zfree_cb;

    if(inflateInit(z) != Z_OK)
      return process_zlib_error(conn, z);
    k->zlib_init = ZLIB_INIT;
  }

  /* Set the compressed input when this function is called */
  z->next_in = (Bytef *)k->str;
  z->avail_in = (uInt)nread;

  /* Now uncompress the data */
  return inflate_stream(conn, k);
}