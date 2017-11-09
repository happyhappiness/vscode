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
    if (Context &&
        !mutt_strcmp (tmp->realpath, Context->realpath))
    {
      tmp->msg_count = Context->msgcount;
      tmp->msg_unread = Context->unread;
    }

    strfcpy (buffer, NONULL (tmp->path), sizeof (buffer));
    mutt_pretty_mailbox (buffer, sizeof (buffer));

#ifdef USE_IMAP
    if (mx_is_imap (tmp->path))
    {
      add_folder (menu, state, buffer, NULL, tmp);
      continue;
    }
#endif
#ifdef USE_POP
    if (mx_is_pop (tmp->path))
    {
      add_folder (menu, state, buffer, NULL, tmp);
      continue;
    }
#endif
    if (lstat (tmp->path, &s) == -1)
      continue;

    if ((! S_ISREG (s.st_mode)) && (! S_ISDIR (s.st_mode)) &&
	(! S_ISLNK (s.st_mode)))
      continue;

    if (mx_is_maildir (tmp->path))
    {
      struct stat st2;
      char md[_POSIX_PATH_MAX];

      snprintf (md, sizeof (md), "%s/new", tmp->path);
      if (stat (md, &s) < 0)
	s.st_mtime = 0;
      snprintf (md, sizeof (md), "%s/cur", tmp->path);
      if (stat (md, &st2) < 0)
	st2.st_mtime = 0;
      if (st2.st_mtime > s.st_mtime)
	s.st_mtime = st2.st_mtime;
    }

    add_folder (menu, state, buffer, &s, tmp);
  }
  while ((tmp = tmp->next));
  browser_sort (state);
  return 0;
}