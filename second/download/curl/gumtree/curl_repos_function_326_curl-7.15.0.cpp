static CURLcode
exit_zlib(z_stream *z, bool *zlib_init, CURLcode result)
{
  inflateEnd(z);
  *zlib_init = ZLIB_UNINIT;
  return result;
}