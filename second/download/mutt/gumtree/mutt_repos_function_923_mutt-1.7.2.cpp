int rfc1524_mailcap_lookup (BODY *a, char *type, rfc1524_entry *entry, int opt)
{
  char path[_POSIX_PATH_MAX];
  int x;
  int found = FALSE;
  char *curr = MailcapPath;

  /* rfc1524 specifies that a path of mailcap files should be searched.
   * joy.  They say 
   * $HOME/.mailcap:/etc/mailcap:/usr/etc/mailcap:/usr/local/etc/mailcap, etc
   * and overridden by the MAILCAPS environment variable, and, just to be nice,
   * we'll make it specifiable in .muttrc
   */
  if (!curr || !*curr)
  {
    mutt_error _("No mailcap path specified");
    return 0;
  }

  mutt_check_lookup_list (a, type, SHORT_STRING);

  while (!found && *curr)
  {
    x = 0;
    while (*curr && *curr != ':' && x < sizeof (path) - 1)
    {
      path[x++] = *curr;
      curr++;
    }
    if (*curr)
      curr++;

    if (!x)
      continue;
    
    path[x] = '\0';
    mutt_expand_path (path, sizeof (path));

    dprint(2,(debugfile,"Checking mailcap file: %s\n",path));
    found = rfc1524_mailcap_parse (a, path, type, entry, opt);
  }

  if (entry && !found)
    mutt_error (_("mailcap entry for type %s not found"), type);

  return found;
}