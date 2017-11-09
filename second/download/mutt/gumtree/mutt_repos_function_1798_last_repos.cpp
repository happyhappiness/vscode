static void candidate (char *dest, char *try, const char *src, int len)
{
  int l;

  if (strstr (src, try) == src)
  {
    matches_ensure_morespace (Num_matched);
    Matches[Num_matched++] = src;
    if (dest[0] == 0)
      strfcpy (dest, src, len);
    else
    {
      for (l = 0; src[l] && src[l] == dest[l]; l++);
      dest[l] = 0;
    }
  }
}