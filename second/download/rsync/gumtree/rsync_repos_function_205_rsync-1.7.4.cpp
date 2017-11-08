int inflateEnd(z)
z_stream *z;
{
  uLong c;

  if (z == Z_NULL || z->state == Z_NULL || z->zfree == Z_NULL)
    return Z_STREAM_ERROR;
  if (z->state->blocks != Z_NULL)
    inflate_blocks_free(z->state->blocks, z, &c);
  ZFREE(z, z->state, sizeof(struct internal_state));
  z->state = Z_NULL;
  Trace((stderr, "inflate: end\n"));
  return Z_OK;
}