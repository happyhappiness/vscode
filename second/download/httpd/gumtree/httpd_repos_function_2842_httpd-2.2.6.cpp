static
int streqci(const char *s1, const char *s2)
{
  for (;;) {
    char c1 = *s1++;
    char c2 = *s2++;
    if (ASCII_a <= c1 && c1 <= ASCII_z)
      c1 += ASCII_A - ASCII_a;
    if (ASCII_a <= c2 && c2 <= ASCII_z)
      c2 += ASCII_A - ASCII_a;
    if (c1 != c2)
      return 0;
    if (!c1)
      break;
  }
  return 1;
}