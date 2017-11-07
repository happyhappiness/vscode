static char *x509_get_part (char *line, const char *ndx)
{
  static char ret[SHORT_STRING];
  char *c, *c2;

  strfcpy (ret, _("Unknown"), sizeof (ret));

  c = strstr (line, ndx);
  if (c)
  {
    c += strlen (ndx);
    c2 = strchr (c, '/');
    if (c2)
      *c2 = '\0';
    strfcpy (ret, c, sizeof (ret));
    if (c2)
      *c2 = '/';
  }

  return ret;
}