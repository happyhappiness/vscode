char *mutt_append_string (char *a, const char *b)
{
  size_t la = mutt_strlen (a);
  safe_realloc ((void **) &a, la + mutt_strlen (b) + 1);
  strcpy (a + la, b);	/* __STRCPY_CHECKED__ */
  return (a);
}