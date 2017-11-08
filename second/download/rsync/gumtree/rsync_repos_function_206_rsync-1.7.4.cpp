int inflateInit2(z, w)
z_stream *z;
int w;
{
  /* initialize state */
  if (z == Z_NULL)
    return Z_STREAM_ERROR;
/*  if (z->zalloc == Z_NULL) z->zalloc = zcalloc; */
/*  if (z->zfree == Z_NULL) z->zfree = zcfree; */
  if ((z->state = (struct internal_state FAR *)
       ZALLOC(z,1,sizeof(struct internal_state))) == Z_NULL)
    return Z_MEM_ERROR;
  z->state->blocks = Z_NULL;

  /* handle undocumented nowrap option (no zlib header or check) */
  z->state->nowrap = 0;
  if (w < 0)
  {
    w = - w;
    z->state->nowrap = 1;
  }

  /* set window size */
  if (w < 8 || w > 15)
  {
    inflateEnd(z);
    return Z_STREAM_ERROR;
  }
  z->state->wbits = (uInt)w;

  /* create inflate_blocks state */
  if ((z->state->blocks =
       inflate_blocks_new(z, z->state->nowrap ? Z_NULL : adler32, 1 << w))
      == Z_NULL)
  {
    inflateEnd(z);
    return Z_MEM_ERROR;
  }
  Trace((stderr, "inflate: allocated\n"));

  /* reset state */
  inflateReset(z);
  return Z_OK;
}