f(inflateInit2(z, -MAX_WBITS) != Z_OK) {
        free(decomp);
        return exit_zlib(z, &k->zlib_init, process_zlib_error(conn, z));
      }