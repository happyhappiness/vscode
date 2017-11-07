static void parse_content_disposition (char *s, BODY *ct)
{
  PARAMETER *parms;

  if (!ascii_strncasecmp ("inline", s, 6))
    ct->disposition = DISPINLINE;
  else if (!ascii_strncasecmp ("form-data", s, 9))
    ct->disposition = DISPFORMDATA;
  else
    ct->disposition = DISPATTACH;

  /* Check to see if a default filename was given */
  if ((s = strchr (s, ';')) != NULL)
  {
    s++;
    SKIPWS (s);
    if ((s = mutt_get_parameter ("filename", (parms = parse_parameters (s)))) != 0)
      mutt_str_replace (&ct->filename, s);
    if ((s = mutt_get_parameter ("name", parms)) != 0)
      ct->form_name = safe_strdup (s);
    mutt_free_parameter (&parms);
  }
}