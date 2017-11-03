short crypt_is_numerical_keyid (const char *s)
{
  /* or should we require the "0x"? */
  if (strncmp (s, "0x", 2) == 0)
    s += 2;
  if (strlen (s) % 8)
    return 0;
  while (*s)
    if (strchr ("0123456789ABCDEFabcdef", *s++) == NULL)
      return 0;

  return 1;
}