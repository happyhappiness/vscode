static CURLcode
inflate_stream(struct SessionHandle *data,
               struct Curl_transfer_keeper *k)
{
  z_stream *z = &k->z;          /* zlib state structure */
  int status;                   /* zlib status */
  CURLcode result = CURLE_OK;   /* Curl_client_write status */
  char *decomp;                 /* Put the decompressed data here. */

  /* Dynamically allocate a buffer for decompression because it's uncommonly
     large to hold on the stack */
  decomp = (char*)malloc(DSIZ);
  if (decomp == NULL) {
    return exit_zlib(z, &k->zlib_init, CURLE_OUT_OF_MEMORY);
  }

  /* because the buffer size is fixed, iteratively decompress and transfer to
     the client via client_write. */
  for (;;) {
    /* (re)set buffer for decompressed output for every iteration */
    z->next_out = (Bytef *)decomp;
    z->avail_out = DSIZ;

    status = inflate(z, Z_SYNC_FLUSH);
    if (status == Z_OK || status == Z_STREAM_END) {
      if(DSIZ - z->avail_out) {
        result = Curl_client_write(data, CLIENTWRITE_BODY, decomp,
                                   DSIZ - z->avail_out);
        /* if !CURLE_OK, clean up, return */
        if (result) {
          free(decomp);
          return exit_zlib(z, &k->zlib_init, result);
        }
      }

      /* Done? clean up, return */
      if (status == Z_STREAM_END) {
        free(decomp);
        if (inflateEnd(z) == Z_OK)
          return exit_zlib(z, &k->zlib_init, result);
        else
          return exit_zlib(z, &k->zlib_init, process_zlib_error(data, z));
      }

      /* Done with these bytes, exit */
      if (status == Z_OK && z->avail_in == 0) {
        free(decomp);
        return result;
      }
    }
    else {                      /* Error; exit loop, handle below */
      free(decomp);
      return exit_zlib(z, &k->zlib_init, process_zlib_error(data, z));
    }
  }
  /* Will never get here */
}