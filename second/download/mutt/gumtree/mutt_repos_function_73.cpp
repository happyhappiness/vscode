static int edit_envelope (ENVELOPE *en)
{
  char buf[HUGE_STRING];
  LIST *uh = UserHeader;

  if (edit_address (&en->to, "To: ") == -1 || en->to == NULL)
    return (-1);
  if (option (OPTASKCC) && edit_address (&en->cc, "Cc: ") == -1)
    return (-1);
  if (option (OPTASKBCC) && edit_address (&en->bcc, "Bcc: ") == -1)
    return (-1);

  if (en->subject)
  {
    if (option (OPTFASTREPLY))
      return (0);
    else
      strfcpy (buf, en->subject, sizeof (buf));
  }
  else
  {
    const char *p;

    buf[0] = 0;
    for (; uh; uh = uh->next)
    {
      if (ascii_strncasecmp ("subject:", uh->data, 8) == 0)
      {
	p = skip_email_wsp(uh->data + 8);
	strncpy (buf, p, sizeof (buf));
      }
    }
  }
  
  if (mutt_get_field ("Subject: ", buf, sizeof (buf), 0) != 0 ||
      (!buf[0] && query_quadoption (OPT_SUBJECT, _("No subject, abort?")) != MUTT_NO))
  {
    mutt_message _("No subject, aborting.");
    return (-1);
  }
  mutt_str_replace (&en->subject, buf);

  return 0;
}