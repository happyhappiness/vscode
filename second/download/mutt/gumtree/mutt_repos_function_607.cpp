static wint_t towlower_ucs (wint_t x)
{
  /* Only works for x < 0x130 */
  if ((0x40 < x && x < 0x5b) || (0xc0 <= x && x < 0xdf && x != 0xd7))
    return x + 32;
  else if (0x100 <= x && x < 0x130)
    return x | 1;
  else
    return x;
}