int mutt_which_case (const char *s)
{
  while (*s)
  {
    if (isalpha ((unsigned char) *s) && isupper ((unsigned char) *s))
      return 0; /* case-sensitive */
    s++;
  }
  return REG_ICASE; /* case-insensitive */
}