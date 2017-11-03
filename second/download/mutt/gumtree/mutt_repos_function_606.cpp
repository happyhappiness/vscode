static int iswupper_ucs (wint_t x)
{
  /* Only works for x < 0x130 */
  if ((0x60 < x && x < 0x7b) || (0xe0 <= x && x < 0xff && x != 0xf7))
    return 0;
  else if ((0x40 < x && x < 0x5b) || (0xbf < x && x < 0xde))
    return 1;
  else if (0x100 <= x && x < 0x130)
    return 1;
  else if (x == 0xb5)
    return 1;
  else if (x == 0xff)
    return 0;
  else
    return 0;
}