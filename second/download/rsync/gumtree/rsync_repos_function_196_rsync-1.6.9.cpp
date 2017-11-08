local void inflate_codes_free(c, z)
inflate_codes_statef *c;
z_stream *z;
{
  ZFREE(z, c, sizeof(struct inflate_codes_state));
  Tracev((stderr, "inflate:       codes free\n"));
}