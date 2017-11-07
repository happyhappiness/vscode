static int examine_mailboxes (MUTTMENU *menu, struct browser_state *state)
{
  struct stat s;
  char buffer[LONG_STRING];
  BUFFY *tmp = Incoming;

  if (!Incoming)
    return (-1);
  mutt_buffy_check (0);

  init_state (state, menu);

  do
  {
#ifdef USE_IMAP
    if (mx_is_imap (tmp->path))
    {
      add_folder (menu, state, tmp->path, NULL, tmp->new);
      continue;
    }
#endif
#ifdef USE_POP
    if (mx_is_pop (tmp->path))
    {
      add_folder (menu, state, tmp->path, NULL, tmp->new);
      continue;
    }
#endif
    if (lstat (tmp->path, &s) == -1)
      continue;

    if ((! S_ISREG (s.st_mode)) && (! S_ISDIR (s.st_mode)) &&
	(! S_ISLNK (s.st_mode)))
      continue;
    
    strfcpy (buffer, NONULL(tmp->path), sizeof (buffer));
    mutt_pretty_mailbox (buffer);

    add_folder (menu, state, buffer, &s, tmp->new);
  }
  while ((tmp = tmp->next));
  browser_sort (state);
  return 0;
}