CURLcode
Curl_unencode_deflate_write(struct SessionHandle *data,
                            struct Curl_transfer_keeper *k,
                            ssize_t nread)
{
  z_stream *z = &k->z;          /* zlib state structure */

  /* Initialize zlib? */
  if (k->zlib_init == ZLIB_UNINIT) {
    z->zalloc = (alloc_func)Z_NULL;
    z->zfree = (free_func)Z_NULL;
    z->opaque = 0;
    z->next_in = NULL;
    z->avail_in = 0;
    if (inflateInit(z) != Z_OK)
      return process_zlib_error(data, z);
    k->zlib_init = ZLIB_INIT;
  }

  /* Set the compressed input when this function is called */
  z->next_in = (Bytef *)k->str;
  z->avail_in = (uInt)nread;

  /* Now uncompress the data */
  return inflate_stream(data, k);
}