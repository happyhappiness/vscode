  {
    adr = iadr;
  }

  if (adr && adr->mailbox)
  {
    strfcpy (buf, adr->mailbox, sizeof (buf));
    if ((pc = strchr (buf, '@')))
      *pc = 0;
  }
  else
    buf[0] = '\0';
  
  /* add a new alias */
  if (mutt_get_field (_("Alias as: "), buf, sizeof (buf), 0) != 0 || !buf[0])
    return;

  /* check to see if the user already has an alias defined */
  if (mutt_lookup_alias (buf))
  {
    mutt_error _("You already have an alias defined with that name!");
    return;
  }

  new       = safe_calloc (1, sizeof (ALIAS));
  new->self = new;
  new->name = safe_strdup (buf);

  if (adr)
    strfcpy (buf, adr->mailbox, sizeof (buf));
  else
    buf[0] = 0;

  do
  {
    if (mutt_get_field (_("Address: "), buf, sizeof (buf), 0) != 0 || !buf[0])
    {
      mutt_free_alias (&new);
      return;
    }
    
    if((new->addr = rfc822_parse_adrlist (new->addr, buf)) == NULL)
      BEEP ();
  }
  while(new->addr == NULL);
  
  if (adr && adr->personal && !mutt_is_mail_list (adr))
    strfcpy (buf, adr->personal, sizeof (buf));
  else
