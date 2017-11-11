static void be_edit_header (ENVELOPE *e, int force)
{
  char tmp[HUGE_STRING];

  move (LINES-1, 0);

  addstr ("To: ");
  tmp[0] = 0;
  mutt_addrlist_to_local (e->to);
  rfc822_write_address (tmp, sizeof (tmp), e->to, 0);
  if (!e->to || force)
  {
    if (mutt_enter_string (tmp, sizeof (tmp), LINES-1, 4, 0) == 0)
    {
      rfc822_free_address (&e->to);
      e->to = mutt_parse_adrlist (e->to, tmp);
      e->to = mutt_expand_aliases (e->to);
      mutt_addrlist_to_intl (e->to, NULL);	/* XXX - IDNA error reporting? */
      tmp[0] = 0;
      rfc822_write_address (tmp, sizeof (tmp), e->to, 1);
      mvaddstr (LINES - 1, 4, tmp);
    }
  }
  else
  {
    mutt_addrlist_to_intl (e->to, NULL);	/* XXX - IDNA error reporting? */
    addstr (tmp);
  }
  addch ('\n');

  if (!e->subject || force)
  {
    addstr ("Subject: ");
    strfcpy (tmp, e->subject ? e->subject: "", sizeof (tmp));
    if (mutt_enter_string (tmp, sizeof (tmp), LINES-1, 9, 0) == 0)
      mutt_str_replace (&e->subject, tmp);
    addch ('\n');
  }

  if ((!e->cc && option (OPTASKCC)) || force)
  {
    addstr ("Cc: ");
    tmp[0] = 0;
    mutt_addrlist_to_local (e->cc);
    rfc822_write_address (tmp, sizeof (tmp), e->cc, 0);
    if (mutt_enter_string (tmp, sizeof (tmp), LINES-1, 4, 0) == 0)
    {
      rfc822_free_address (&e->cc);
      e->cc = mutt_parse_adrlist (e->cc, tmp);
      e->cc = mutt_expand_aliases (e->cc);
      tmp[0] = 0;
      mutt_addrlist_to_intl (e->cc, NULL);
      rfc822_write_address (tmp, sizeof (tmp), e->cc, 1);
      mvaddstr (LINES - 1, 4, tmp);
    }
    else
      mutt_addrlist_to_intl (e->cc, NULL);
    addch ('\n');
  }

  if (option (OPTASKBCC) || force)
  {
    addstr ("Bcc: ");
    tmp[0] = 0;
    mutt_addrlist_to_local (e->bcc);
    rfc822_write_address (tmp, sizeof (tmp), e->bcc, 0);
    if (mutt_enter_string (tmp, sizeof (tmp), LINES-1, 5, 0) == 0)
    {
      rfc822_free_address (&e->bcc);
      e->bcc = mutt_parse_adrlist (e->bcc, tmp);
      e->bcc = mutt_expand_aliases (e->bcc);
      mutt_addrlist_to_intl (e->bcc, NULL);
      tmp[0] = 0;
      rfc822_write_address (tmp, sizeof (tmp), e->bcc, 1);
      mvaddstr (LINES - 1, 5, tmp);
    }
    else
      mutt_addrlist_to_intl (e->bcc, NULL);
    addch ('\n');
  }
}