static int pgpring_string_matches_hint (const char *s, const char *hints[], int nhints)
{
  int i;

  if (!hints || !nhints)
    return 1;

  for (i = 0; i < nhints; i++)
  {
    if (mutt_stristr (s, hints[i]) != NULL)
      return 1;
  }

  return 0;
}