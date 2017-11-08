int inflateInit(z)
z_stream *z;
{
  return inflateInit2(z, DEF_WBITS);
}