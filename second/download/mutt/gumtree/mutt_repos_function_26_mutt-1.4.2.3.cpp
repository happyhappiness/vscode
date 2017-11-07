static int edit_address (ADDRESS **a, /* const */ char *field)
{
  char buf[HUGE_STRING];

  buf[0] = 0;
  rfc822_write_address (buf, sizeof (buf), *a);
  if (mutt_get_field (field, buf, sizeof (buf), M_ALIAS) != 0)
    return (-1);
  rfc822_free_address (a);
  *a = mutt_expand_aliases (mutt_parse_adrlist (NULL, buf));
  return 0;
}