{
      /* zlib ver. >= 1.2.0.4 supports transparent gzip decompressing */
      if(inflateInit2(z, MAX_WBITS+32) != Z_OK) {
        return process_zlib_error(conn, z);
      }
      k->zlib_init = ZLIB_INIT_GZIP; /* Transparent gzip decompress state */
    }