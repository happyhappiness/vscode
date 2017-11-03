static int iswalpha_ucs (wint_t wc)
{
  /* Only works for x < 0x220 */
  if (wc >= 0x100)
    return 1;
  else if (wc < 0x3a)
    return 0;
  else if (wc < 0xa0)
    return (0x40 < (wc & ~0x20) && (wc & ~0x20) < 0x5b);
  else if (wc < 0xc0)
    return (wc == 0xaa || wc == 0xb5 || wc == 0xba);
  else
    return !(wc == 0xd7 || wc == 0xf7);
}