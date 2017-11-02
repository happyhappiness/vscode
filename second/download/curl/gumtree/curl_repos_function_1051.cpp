static CURLcode
inflate_stream(struct connectdata *conn,
               struct SingleRequest *k)
{
  int allow_restart = 1;
  z_stream *z = &k->z;          /* zlib state structure */
  uInt nread = z->avail_in;
  Bytef *orig_in = z->next_in;
  int status;                   /* zlib status */
  CURLcode result = CURLE_OK;   /* Curl_client_write status */
  char *decomp;                 /* Put the decompressed data here. */

  /* Dynamically allocate a buffer for decompression because it's uncommonly
     large to hold on the stack */
  decomp = malloc(DSIZ);
  if(decomp == NULL) {
    return exit_zlib(z, &k->zlib_init, CURLE_OUT_OF_MEMORY);
  }

  /* because the buffer size is fixed, iteratively decompress and transfer to
     the client via client_write. */
  for(;;) {
    /* (re)set buffer for decompressed output for every iteration */
    z->next_out = (Bytef *)decomp;
    z->avail_out = DSIZ;

    status = inflate(z, Z_SYNC_FLUSH);
    if(status == Z_OK || status == Z_STREAM_END) {
      allow_restart = 0;
      if((DSIZ - z->avail_out) && (!k->ignorebody)) {
        result = Curl_client_write(conn, CLIENTWRITE_BODY, decomp,
                                   DSIZ - z->avail_out);
        /* if !CURLE_OK, clean up, return */
        if(result) {
          free(decomp);
          return exit_zlib(z, &k->zlib_init, result);
        }
      }

      /* Done? clean up, return */
      if(status == Z_STREAM_END) {
        free(decomp);
        if(inflateEnd(z) == Z_OK)
          return exit_zlib(z, &k->zlib_init, result);
        else
          return exit_zlib(z, &k->zlib_init, process_zlib_error(conn, z));
      }

      /* Done with these bytes, exit */

      /* status is always Z_OK at this point! */
      if(z->avail_in == 0) {
        free(decomp);
        return result;
      }
    }
    else if(allow_restart && status == Z_DATA_ERROR) {
      /* some servers seem to not generate zlib headers, so this is an attempt
         to fix and continue anyway */

      (void) inflateEnd(z);     /* don't care about the return code */
      if(inflateInit2(z, -MAX_WBITS) != Z_OK) {
        free(decomp);
        return exit_zlib(z, &k->zlib_init, process_zlib_error(conn, z));
      }
      z->next_in = orig_in;
      z->avail_in = nread;
      allow_restart = 0;
      continue;
    }
    else {                      /* Error; exit loop, handle below */
      free(decomp);
      return exit_zlib(z, &k->zlib_init, process_zlib_error(conn, z));
    }
  }
  /* Will never get here */
}