static int examine_directory (MUTTMENU *menu, struct browser_state *state,
			      char *d, const char *prefix)
{
  struct stat s;
  DIR *dp;
  struct dirent *de;
  char buffer[_POSIX_PATH_MAX + SHORT_STRING];
  BUFFY *tmp;

  while (stat (d, &s) == -1)
  {
    if (errno == ENOENT)
    {
      /* The last used directory is deleted, try to use the parent dir. */
      char *c = strrchr (d, '/');

      if (c && (c > d))
      {
	*c = 0;
	continue;
      }
    }
    mutt_perror (d);
    return (-1);
  }

  if (!S_ISDIR (s.st_mode))
  {
    mutt_error (_("%s is not a directory."), d);
    return (-1);
  }

  mutt_buffy_check (0);

  if ((dp = opendir (d)) == NULL)
  {
    mutt_perror (d);
    return (-1);
  }

  init_state (state, menu);

  while ((de = readdir (dp)) != NULL)
  {
    if (mutt_strcmp (de->d_name, ".") == 0)
      continue;    /* we don't need . */
    
    if (prefix && *prefix && mutt_strncmp (prefix, de->d_name, mutt_strlen (prefix)) != 0)
      continue;
    if (!((regexec (Mask.rx, de->d_name, 0, NULL, 0) == 0) ^ Mask.not))
      continue;

    mutt_concat_path (buffer, d, de->d_name, sizeof (buffer));
    if (lstat (buffer, &s) == -1)
      continue;
    
    if ((! S_ISREG (s.st_mode)) && (! S_ISDIR (s.st_mode)) &&
	(! S_ISLNK (s.st_mode)))
      continue;
    
    tmp = Incoming;
    while (tmp && mutt_strcmp (buffer, tmp->path))
      tmp = tmp->next;
    if (tmp && Context &&
        !mutt_strcmp (tmp->realpath, Context->realpath))
    {
      tmp->msg_count = Context->msgcount;
      tmp->msg_unread = Context->unread;
    }
    add_folder (menu, state, de->d_name, &s, tmp);
  }
  closedir (dp);  
  browser_sort (state);
  return 0;
}