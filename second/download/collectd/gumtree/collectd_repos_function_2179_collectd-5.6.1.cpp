static int lu_copy_ident_to_match_part (part_match_t *match_part, /* {{{ */
    char const *ident_part)
{
  size_t len = strlen (ident_part);
  int status;

  if ((len < 3) || (ident_part[0] != '/') || (ident_part[len - 1] != '/'))
  {
    sstrncpy (match_part->str, ident_part, sizeof (match_part->str));
    match_part->is_regex = 0;
    return (0);
  }

  /* Copy string without the leading slash. */
  sstrncpy (match_part->str, ident_part + 1, sizeof (match_part->str));
  assert (sizeof (match_part->str) > len);
  /* strip trailing slash */
  match_part->str[len - 2] = 0;

  status = regcomp (&match_part->regex, match_part->str,
      /* flags = */ REG_EXTENDED);
  if (status != 0)
  {
    char errbuf[1024];
    regerror (status, &match_part->regex, errbuf, sizeof (errbuf));
    ERROR ("utils_vl_lookup: Compiling regular expression \"%s\" failed: %s",
        match_part->str, errbuf);
    return (EINVAL);
  }
  match_part->is_regex = 1;

  return (0);
}