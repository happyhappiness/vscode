void ci_bounce_message (HEADER *h, int *redraw)
{
  char prompt[SHORT_STRING];
  char buf[HUGE_STRING] = { 0 };
  ADDRESS *adr = NULL;
  int rc;

  if(h)
    strfcpy(prompt, _("Bounce message to: "), sizeof(prompt));
  else
    strfcpy(prompt, _("Bounce tagged messages to: "), sizeof(prompt));
  
  rc = mutt_get_field (prompt, buf, sizeof (buf), M_ALIAS);

  if (option (OPTNEEDREDRAW))
  {
    unset_option (OPTNEEDREDRAW);
    *redraw = REDRAW_FULL;
  }

  if (rc || !buf[0])
    return;

  if (!(adr = rfc822_parse_adrlist (adr, buf)))
  {
    mutt_error _("Error parsing address!");
    return;
  }

  adr = mutt_expand_aliases (adr);

  buf[0] = 0;
  rfc822_write_address (buf, sizeof (buf), adr);

#define extra_space (15 + 7 + 2)
  /*
   * This is the printing width of "...? ([y=yes]/n=no): ?" plus 2
   * for good measure. This is not ideal. FIXME.
   */
  snprintf (prompt, sizeof (prompt) - 4,
           (h ? _("Bounce message to %s") : _("Bounce messages to %s")), buf);
  mutt_format_string (prompt, sizeof (prompt) - 4,
		      0, COLS-extra_space, 0, 0,
		      prompt, sizeof (prompt), 0);
  strcat (prompt, "...?");	/* __STRCAT_CHECKED__ */
  if (mutt_yesorno (prompt, 1) != 1)
  {
    rfc822_free_address (&adr);
    CLEARLINE (LINES-1);
    return;
  }

  mutt_bounce_message (NULL, h, adr);
  rfc822_free_address (&adr);
  mutt_message (h ? _("Message bounced.") : _("Messages bounced."));
}