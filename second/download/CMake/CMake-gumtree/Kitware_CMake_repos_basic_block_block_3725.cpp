{
        free(decomp);
        if(inflateEnd(z) == Z_OK)
          return exit_zlib(z, &k->zlib_init, result);
        return exit_zlib(z, &k->zlib_init, process_zlib_error(conn, z));
      }