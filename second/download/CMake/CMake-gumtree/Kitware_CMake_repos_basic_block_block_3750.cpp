f(inflateInit2(z, -MAX_WBITS) != Z_OK) {
        return process_zlib_error(conn, z);
      }