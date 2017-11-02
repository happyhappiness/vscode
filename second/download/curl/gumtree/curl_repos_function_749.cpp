void hugehelp(void)
{
  unsigned char* buf;
  int status,headerlen;
  z_stream z;

  /* Make sure no gzip options are set */
  if (hugehelpgz[3] & 0xfe)
    return;

  headerlen = 10;
  memset(&z, 0, sizeof(z_stream));
  z.zalloc = (alloc_func)zalloc_func;
  z.zfree = (free_func)zfree_func;
  z.avail_in = (unsigned int)(sizeof(hugehelpgz) - headerlen);
  z.next_in = (unsigned char *)hugehelpgz + headerlen;

  if (inflateInit2(&z, -MAX_WBITS) != Z_OK)
    return;

  buf = malloc(BUF_SIZE);
  if (buf) {
    while(1) {
      z.avail_out = BUF_SIZE;
      z.next_out = buf;
      status = inflate(&z, Z_SYNC_FLUSH);
      if (status == Z_OK || status == Z_STREAM_END) {
        fwrite(buf, BUF_SIZE - z.avail_out, 1, stdout);
        if (status == Z_STREAM_END)
          break;
      }
      else
        break;    /* Error */
    }
    free(buf);
  }
  inflateEnd(&z);
}