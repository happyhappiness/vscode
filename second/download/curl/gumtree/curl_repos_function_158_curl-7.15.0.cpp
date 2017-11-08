void hugehelp(void)
{
  unsigned char buf[0x10000];
  int status,headerlen;
  z_stream z;

  /* Make sure no gzip options are set */
  if (hugehelpgz[3] & 0xfe)
    return;

  headerlen = 10;
  z.avail_in = sizeof(hugehelpgz) - headerlen;
  z.next_in = (unsigned char *)hugehelpgz + headerlen;
  z.zalloc = (alloc_func)Z_NULL;
  z.zfree = (free_func)Z_NULL;
  z.opaque = 0;

  if (inflateInit2(&z, -MAX_WBITS) != Z_OK)
    return;

  while(1) {
    z.avail_out = (int)sizeof(buf);
    z.next_out = buf;
    status = inflate(&z, Z_SYNC_FLUSH);
    if (status == Z_OK || status == Z_STREAM_END) {
      fwrite(buf, sizeof(buf) - z.avail_out, 1, stdout);
      if (status == Z_STREAM_END)
         break;
    }
     else
      break;    /* Error */
  }
  inflateEnd(&z);
}