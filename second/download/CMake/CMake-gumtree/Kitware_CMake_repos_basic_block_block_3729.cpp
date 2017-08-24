f((DSIZ - z->avail_out) && (!k->ignorebody)) {
        result = Curl_client_write(conn, CLIENTWRITE_BODY, decomp,
                                   DSIZ - z->avail_out);
        /* if !CURLE_OK, clean up, return */
        if(result) {
          free(decomp);
          return exit_zlib(z, &k->zlib_init, result);
        }
      }