int inflate_blocks_free(s, z)
inflate_blocks_statef *s;
z_streamp z;
{
  inflate_blocks_reset(s, z, Z_NULL);
  ZFREE(z, s->window);
  ZFREE(z, s->hufts);
  ZFREE(z, s);
  Tracev((stderr, "inflate:   blocks freed\n"));
  return Z_OK;
}