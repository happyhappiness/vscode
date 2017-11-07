static void parse_content_disposition (const char *s, BODY *ct)
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
    s = skip_email_wsp(s + 1);
    if ((s = mutt_get_parameter ("filename", (parms = parse_parameters (s)))))
      mutt_str_replace (&ct->filename, s);
    if ((s = mutt_get_parameter ("name", parms)))
      ct->form_name = safe_strdup (s);
    mutt_free_parameter (&parms);
  }
}