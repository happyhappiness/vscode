local int inflate_blocks_free(s, z, c)
inflate_blocks_statef *s;
z_stream *z;
uLongf *c;
{
  inflate_blocks_reset(s, z, c);
  ZFREE(z, s->window, s->end - s->window);
  ZFREE(z, s, sizeof(struct inflate_blocks_state));
  Trace((stderr, "inflate:   blocks freed\n"));
  return Z_OK;
}