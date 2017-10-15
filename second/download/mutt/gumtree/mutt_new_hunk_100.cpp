 **/

void mutt_attach_bounce (FILE * fp, HEADER * hdr, 
	   ATTACHPTR ** idx, short idxlen, BODY * cur)
{
  short i;
  char prompt[STRING];
  char buf[HUGE_STRING];
  char *err = NULL;
  ADDRESS *adr = NULL;
  int ret = 0;
  int p   = 0;

  if (check_all_msg (idx, idxlen, cur, 1) == -1)
    return;

  /* one or more messages? */
  p = (cur || count_tagged (idx, idxlen) == 1);

  /* RfC 5322 mandates a From: header, so warn before bouncing
   * messages without one */
  if (cur)
  {
    if (!cur->hdr->env->from)
    {
      mutt_error _("Warning: message contains no From: header");
      mutt_sleep (2);
      mutt_clear_error ();
    }
  }
  else
  {
    for (i = 0; i < idxlen; i++)
    {
      if (idx[i]->content->tagged)
      {
	if (!idx[i]->content->hdr->env->from)
	{
	  mutt_error _("Warning: message contains no From: header");
	  mutt_sleep (2);
	  mutt_clear_error ();
	  break;
	}
      }
    }
  }

  if (p)
    strfcpy (prompt, _("Bounce message to: "), sizeof (prompt));
  else
    strfcpy (prompt, _("Bounce tagged messages to: "), sizeof (prompt));

  buf[0] = '\0';
  if (mutt_get_field (prompt, buf, sizeof (buf), M_ALIAS) 
      || buf[0] == '\0')
    return;

  if (!(adr = rfc822_parse_adrlist (adr, buf)))
  {
    mutt_error _("Error parsing address!");
    return;
  }

  adr = mutt_expand_aliases (adr);
  
  if (mutt_addrlist_to_idna (adr, &err) < 0)
  {
    mutt_error (_("Bad IDN: '%s'"), err);
    FREE (&err);
    rfc822_free_address (&adr);
    return;
  }
  
  buf[0] = 0;
  rfc822_write_address (buf, sizeof (buf), adr, 1);

#define extra_space (15+7+2)
  /*
   * See commands.c.
   */
  snprintf (prompt, sizeof (prompt) - 4, 
   (p ? _("Bounce message to %s") : _("Bounce messages to %s")), buf);
  
  if (mutt_strwidth (prompt) > COLS - extra_space)
  {
    mutt_format_string (prompt, sizeof (prompt) - 4,
			0, COLS-extra_space, FMT_LEFT, 0,
			prompt, sizeof (prompt), 0);
    safe_strcat (prompt, sizeof (prompt), "...?");
  }
  else
    safe_strcat (prompt, sizeof (prompt), "?");

  if (query_quadoption (OPT_BOUNCE, prompt) != M_YES)
  {
    rfc822_free_address (&adr);
    CLEARLINE (LINES - 1);
    mutt_message (p ? _("Message not bounced.") : _("Messages not bounced."));
    return;
  }
  
  CLEARLINE (LINES - 1);
  
  if (cur)
    ret = mutt_bounce_message (fp, cur->hdr, adr);
  else
  {
    for (i = 0; i < idxlen; i++)
    {
      if (idx[i]->content->tagged)
	if (mutt_bounce_message (fp, idx[i]->content->hdr, adr))
	  ret = 1;
    }
  }

  if (!ret)
    mutt_message (p ? _("Message bounced.") : _("Messages bounced."));
  else
    mutt_error (p ? _("Error bouncing message!") : _("Error bouncing messages!"));
}



/**
 **
