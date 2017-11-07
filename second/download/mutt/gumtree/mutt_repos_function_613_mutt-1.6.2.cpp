void mutt_create_alias (ENVELOPE *cur, ADDRESS *iadr)
{
  ALIAS *new, *t;
  char buf[LONG_STRING], tmp[LONG_STRING], prompt[SHORT_STRING], *pc;
  char *err = NULL;
  char fixed[LONG_STRING];
  FILE *rc;
  ADDRESS *adr = NULL;

  if (cur)
  {
    adr = mutt_get_address (cur, NULL);
  }
  else if (iadr)
  {
    adr = iadr;
  }

  if (adr && adr->mailbox)
  {
    strfcpy (tmp, adr->mailbox, sizeof (tmp));
    if ((pc = strchr (tmp, '@')))
      *pc = 0;
  }
  else
    tmp[0] = '\0';

  /* Don't suggest a bad alias name in the event of a strange local part. */
  mutt_check_alias_name (tmp, buf, sizeof (buf));
  
retry_name:
  /* L10N: prompt to add a new alias */
  if (mutt_get_field (_("Alias as: "), buf, sizeof (buf), 0) != 0 || !buf[0])
    return;

  /* check to see if the user already has an alias defined */
  if (mutt_lookup_alias (buf))
  {
    mutt_error _("You already have an alias defined with that name!");
    return;
  }
  
  if (mutt_check_alias_name (buf, fixed, sizeof (fixed)))
  {
    switch (mutt_yesorno (_("Warning: This alias name may not work.  Fix it?"), M_YES))
    {
      case M_YES:
      	strfcpy (buf, fixed, sizeof (buf));
	goto retry_name;
      case -1: 
	return;
    }
  }
  
  new       = safe_calloc (1, sizeof (ALIAS));
  new->self = new;
  new->name = safe_strdup (buf);

  mutt_addrlist_to_local (adr);
  
  if (adr)
    strfcpy (buf, adr->mailbox, sizeof (buf));
  else
    buf[0] = 0;

  mutt_addrlist_to_intl (adr, NULL);
  
  do
  {
    if (mutt_get_field (_("Address: "), buf, sizeof (buf), 0) != 0 || !buf[0])
    {
      mutt_free_alias (&new);
      return;
    }
    
    if((new->addr = rfc822_parse_adrlist (new->addr, buf)) == NULL)
      BEEP ();
    if (mutt_addrlist_to_intl (new->addr, &err))
    {
      mutt_error (_("Error: '%s' is a bad IDN."), err);
      mutt_sleep (2);
      continue;
    }
  }
  while(new->addr == NULL);
  
  if (adr && adr->personal && !mutt_is_mail_list (adr))
    strfcpy (buf, adr->personal, sizeof (buf));
  else
    buf[0] = 0;

  if (mutt_get_field (_("Personal name: "), buf, sizeof (buf), 0) != 0)
  {
    mutt_free_alias (&new);
    return;
  }
  new->addr->personal = safe_strdup (buf);

  buf[0] = 0;
  rfc822_write_address (buf, sizeof (buf), new->addr, 1);
  snprintf (prompt, sizeof (prompt), _("[%s = %s] Accept?"), new->name, buf);
  if (mutt_yesorno (prompt, M_YES) != M_YES)
  {
    mutt_free_alias (&new);
    return;
  }

  mutt_alias_add_reverse (new);
  
  if ((t = Aliases))
  {
    while (t->next)
      t = t->next;
    t->next = new;
  }
  else
    Aliases = new;

  strfcpy (buf, NONULL (AliasFile), sizeof (buf));
  if (mutt_get_field (_("Save to file: "), buf, sizeof (buf), M_FILE) != 0)
    return;
  mutt_expand_path (buf, sizeof (buf));
  if ((rc = fopen (buf, "a+")))
  {
    /* terminate existing file with \n if necessary */
    if (fseek (rc, 0, SEEK_END))
      goto fseek_err;
    if (ftell(rc) > 0)
    {
      if (fseek (rc, -1, SEEK_CUR) < 0)
	goto fseek_err;
      if (fread(buf, 1, 1, rc) != 1)
      {
	mutt_perror (_("Error reading alias file"));
	safe_fclose (&rc);
	return;
      }
      if (fseek (rc, 0, SEEK_END) < 0)
	goto fseek_err;
      if (buf[0] != '\n')
	fputc ('\n', rc);
    }

    if (mutt_check_alias_name (new->name, NULL, 0))
      mutt_quote_filename (buf, sizeof (buf), new->name);
    else
      strfcpy (buf, new->name, sizeof (buf));
    recode_buf (buf, sizeof (buf));
    fprintf (rc, "alias %s ", buf);
    buf[0] = 0;
    rfc822_write_address (buf, sizeof (buf), new->addr, 0);
    recode_buf (buf, sizeof (buf));
    write_safe_address (rc, buf);
    fputc ('\n', rc);
    safe_fclose (&rc);
    mutt_message _("Alias added.");
  }
  else
    mutt_perror (buf);

  return;
  
  fseek_err:
  mutt_perror (_("Error seeking in alias file"));
  safe_fclose (&rc);
  return;
}