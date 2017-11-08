void inflate_codes_free(c, z)
inflate_codes_statef *c;
z_streamp z;
{
  ZFREE(z, c);
  Tracev((stderr, "inflate:       codes free\n"));
}