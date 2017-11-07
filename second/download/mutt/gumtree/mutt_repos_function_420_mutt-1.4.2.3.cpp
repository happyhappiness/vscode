void mutt_create_alias (ENVELOPE *cur, ADDRESS *iadr)
{
  ALIAS *new, *t;
  char buf[LONG_STRING], prompt[SHORT_STRING], *pc;
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
    buf[0] = 0;

  if (mutt_get_field (_("Personal name: "), buf, sizeof (buf), 0) != 0)
  {
    mutt_free_alias (&new);
    return;
  }
  new->addr->personal = safe_strdup (buf);

  buf[0] = 0;
  rfc822_write_address (buf, sizeof (buf), new->addr);
  snprintf (prompt, sizeof (prompt), _("[%s = %s] Accept?"), new->name, buf);
  if (mutt_yesorno (prompt, 1) != 1)
  {
    mutt_free_alias (&new);
    return;
  }

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
  if ((rc = fopen (buf, "a")))
  {
    buf[0] = 0;
    rfc822_write_address (buf, sizeof (buf), new->addr);
    fprintf (rc, "alias %s ", new->name);
    write_safe_address (rc, buf);
    fputc ('\n', rc);
    fclose (rc);
    mutt_message _("Alias added.");
  }
  else
    mutt_perror (buf);
}