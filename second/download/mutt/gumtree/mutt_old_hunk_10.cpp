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

static void pipe_set_flags (int decode, int print, int *cmflags, int *chflags)
{
  if (decode)
  {
