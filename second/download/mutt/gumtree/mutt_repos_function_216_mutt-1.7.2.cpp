void ci_bounce_message (HEADER *h, int *redraw)
{
  char prompt[SHORT_STRING];
  char scratch[SHORT_STRING];
  char buf[HUGE_STRING] = { 0 };
  ADDRESS *adr = NULL;
  char *err = NULL;
  int rc;

 /* RfC 5322 mandates a From: header, so warn before bouncing
  * messages without one */
  if (h)
  {
    if (!h->env->from)
    {
      mutt_error _("Warning: message contains no From: header");
      mutt_sleep (2);
    }
  }
  else if (Context)
  {
    for (rc = 0; rc < Context->msgcount; rc++)
    {
      if (Context->hdrs[rc]->tagged && !Context->hdrs[rc]->env->from)
      {
	mutt_error _("Warning: message contains no From: header");
	mutt_sleep (2);
	break;
      }
    }
  }

  if(h)
    strfcpy(prompt, _("Bounce message to: "), sizeof(prompt));
  else
    strfcpy(prompt, _("Bounce tagged messages to: "), sizeof(prompt));
  
  rc = mutt_get_field (prompt, buf, sizeof (buf), MUTT_ALIAS);

  if (option (OPTNEEDREDRAW))
  {
    unset_option (OPTNEEDREDRAW);
    *redraw = REDRAW_FULL;
  }

  if (rc || !buf[0])
    return;

  if (!(adr = mutt_parse_adrlist (adr, buf)))
  {
    mutt_error _("Error parsing address!");
    return;
  }

  adr = mutt_expand_aliases (adr);

  if (mutt_addrlist_to_intl (adr, &err) < 0)
  {
    mutt_error (_("Bad IDN: '%s'"), err);
    FREE (&err);
    rfc822_free_address (&adr);
    return;
  }

  buf[0] = 0;
  rfc822_write_address (buf, sizeof (buf), adr, 1);

#define extra_space (15 + 7 + 2)
  snprintf (scratch, sizeof (scratch),
           (h ? _("Bounce message to %s") : _("Bounce messages to %s")), buf);

  if (mutt_strwidth (prompt) > MuttMessageWindow->cols - extra_space)
  {
    mutt_format_string (prompt, sizeof (prompt),
			0, MuttMessageWindow->cols-extra_space, FMT_LEFT, 0,
			scratch, sizeof (scratch), 0);
    safe_strcat (prompt, sizeof (prompt), "...?");
  }
  else
    snprintf (prompt, sizeof (prompt), "%s?", scratch);

  if (query_quadoption (OPT_BOUNCE, prompt) != MUTT_YES)
  {
    rfc822_free_address (&adr);
    mutt_window_clearline (MuttMessageWindow, 0);
    mutt_message (h ? _("Message not bounced.") : _("Messages not bounced."));
    return;
  }

  mutt_window_clearline (MuttMessageWindow, 0);
  
  rc = mutt_bounce_message (NULL, h, adr);
  rfc822_free_address (&adr);
  /* If no error, or background, display message. */
  if ((rc == 0) || (rc == S_BKG))
    mutt_message (h ? _("Message bounced.") : _("Messages bounced."));
}