void mutt_attach_bounce (FILE * fp, HEADER * hdr, 
	   ATTACHPTR ** idx, short idxlen, BODY * cur)
{
  short i;
  short ntagged;
  char prompt[STRING];
  char buf[HUGE_STRING];
  ADDRESS *adr = NULL;

  if (check_all_msg (idx, idxlen, cur, 1) == -1)
    return;

  ntagged = count_tagged (idx, idxlen);
  
  if (cur || ntagged == 1)
    strfcpy (prompt, _("Bounce message to: "), sizeof (prompt));
  else
    strfcpy (prompt, _("Bounce tagged messages to: "), sizeof (prompt));

  buf[0] = '\0';
  if (mutt_get_field (prompt, buf, sizeof (buf), M_ALIAS) 
      || buf[0] == '\0')
    return;

  adr = rfc822_parse_adrlist (adr, buf);
  adr = mutt_expand_aliases (adr);
  buf[0] = 0;
  rfc822_write_address (buf, sizeof (buf), adr);

  snprintf (prompt, sizeof (prompt), 
	    cur ? _("Bounce message to %s...?") :  _("Bounce messages to %s...?"), buf);

  if (mutt_yesorno (prompt, 1) != 1)
    goto bail;

  if (cur)
    mutt_bounce_message (fp, cur->hdr, adr);
  else
  {
    for (i = 0; i < idxlen; i++)
    {
      if (idx[i]->content->tagged)
	mutt_bounce_message (fp, idx[i]->content->hdr, adr);
    }
  }

bail:

  rfc822_free_address (&adr);
  CLEARLINE (LINES - 1);
}