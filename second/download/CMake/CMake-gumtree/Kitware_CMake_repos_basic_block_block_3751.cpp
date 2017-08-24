{
    memset(z, 0, sizeof(z_stream));
    z->zalloc = (alloc_func)zalloc_cb;
    z->zfree = (free_func)zfree_cb;

    if(strcmp(zlibVersion(), "1.2.0.4") >= 0) {
      /* zlib ver. >= 1.2.0.4 supports transparent gzip decompressing */
      if(inflateInit2(z, MAX_WBITS+32) != Z_OK) {
        return process_zlib_error(conn, z);
      }
      k->zlib_init = ZLIB_INIT_GZIP; /* Transparent gzip decompress state */
    }
    else {
      /* we must parse the gzip header ourselves */
      if(inflateInit2(z, -MAX_WBITS) != Z_OK) {
        return process_zlib_error(conn, z);
      }
      k->zlib_init = ZLIB_INIT;   /* Initial call state */
    }
  }