static void skip_bignum (unsigned char *buff, size_t l, size_t j,
			 size_t * toff, size_t n)
{
  size_t len;

  do
  {
    len = (buff[j] << 8) + buff[j + 1];
    j += (len + 7) / 8 + 2;
  }
  while (j <= l && --n > 0);

  if (toff)
    *toff = j;
}