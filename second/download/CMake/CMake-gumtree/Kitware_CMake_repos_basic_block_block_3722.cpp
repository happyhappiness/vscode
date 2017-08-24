{
        free(decomp);
        return exit_zlib(z, &k->zlib_init, process_zlib_error(conn, z));
      }