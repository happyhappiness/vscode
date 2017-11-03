static wint_t towupper_ucs (wint_t x)
{
  /* Only works for x < 0x130 */
  if ((0x60 < x && x < 0x7b) || (0xe0 <= x && x < 0xff && x != 0xf7))
    return x - 32;
  else if (0x100 <= x && x < 0x130)
    return x & ~1;
  else if (x == 0xb5)
    return 0x39c;
  else if (x == 0xff)
    return 0x178;
  else
    return x;
}