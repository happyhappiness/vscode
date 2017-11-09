int mutt_get_field_unbuffered (char *msg, char *buf, size_t buflen, int flags)
{
  int rc;

  set_option (OPTIGNOREMACROEVENTS);
  rc = mutt_get_field (msg, buf, buflen, flags);
  unset_option (OPTIGNOREMACROEVENTS);

  return (rc);
}