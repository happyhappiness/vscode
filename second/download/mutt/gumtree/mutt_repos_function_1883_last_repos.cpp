static LIST *pgp_add_string_to_hints (LIST *hints, const char *str)
{
  char *scratch;
  char *t;

  if ((scratch = safe_strdup (str)) == NULL)
    return hints;

  for (t = strtok (scratch, " ,.:\"()<>\n"); t;
       		t = strtok (NULL, " ,.:\"()<>\n"))
  {
    if (strlen (t) > 3)
      hints = mutt_add_list (hints, t);
  }

  FREE (&scratch);
  return hints;
}