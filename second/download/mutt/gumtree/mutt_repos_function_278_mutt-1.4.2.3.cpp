int mutt_buffy_check (int force)
{
  BUFFY *tmp;
  struct stat sb;
  struct dirent *de;
  DIR *dirp;
  char path[_POSIX_PATH_MAX];
  struct stat contex_sb;
  time_t t;

#ifdef USE_IMAP
  /* update postponed count as well, on force */
  if (force)
    mutt_update_num_postponed ();
#endif

  /* fastest return if there are no mailboxes */
  if (!Incoming)
    return 0;
  t = time (NULL);
  if (!force && (t - BuffyTime < BuffyTimeout))
    return BuffyCount;
 
  BuffyTime = t;
  BuffyCount = 0;
  BuffyNotify = 0;

#ifdef USE_IMAP
  if (!Context || Context->magic != M_IMAP)
#endif
#ifdef USE_POP
  if (!Context || Context->magic != M_POP)
#endif
  /* check device ID and serial number instead of comparing paths */
  if (!Context || !Context->path || stat (Context->path, &contex_sb) != 0)
  {
    contex_sb.st_dev=0;
    contex_sb.st_ino=0;
  }
  
  for (tmp = Incoming; tmp; tmp = tmp->next)
  {
    tmp->new = 0;

#ifdef USE_IMAP
    if (mx_is_imap (tmp->path))
      tmp->magic = M_IMAP;
    else
#endif
#ifdef USE_POP
    if (mx_is_pop (tmp->path))
      tmp->magic = M_POP;
    else
#endif
    if (stat (tmp->path, &sb) != 0 || sb.st_size == 0 ||
	(!tmp->magic && (tmp->magic = mx_get_magic (tmp->path)) <= 0))
    {
      /* if the mailbox still doesn't exist, set the newly created flag to
       * be ready for when it does. */
      tmp->newly_created = 1;
      tmp->magic = 0;
#ifdef BUFFY_SIZE
      tmp->size = 0;
#endif
      continue;
    }

    /* check to see if the folder is the currently selected folder
     * before polling */
    if (!Context || !Context->path ||
#if defined USE_IMAP || defined USE_POP
	((
#ifdef USE_IMAP
	tmp->magic == M_IMAP
#endif
#ifdef USE_POP
#ifdef USE_IMAP
	||
#endif
	tmp->magic == M_POP
#endif
	) ? mutt_strcmp (tmp->path, Context->path) :
#endif
	 (sb.st_dev != contex_sb.st_dev || sb.st_ino != contex_sb.st_ino)
#if defined USE_IMAP || defined USE_POP	 
	    )
#endif
	)
	
    {
      switch (tmp->magic)
      {
      case M_MBOX:
      case M_MMDF:
      case M_KENDRA:

	if (STAT_CHECK)
	{
	  BuffyCount++;
	  tmp->new = 1;
	}
#ifdef BUFFY_SIZE
	else
	{
	  /* some other program has deleted mail from the folder */
	  tmp->size = (long) sb.st_size;
	}
#endif
	if (tmp->newly_created &&
	    (sb.st_ctime != sb.st_mtime || sb.st_ctime != sb.st_atime))
	  tmp->newly_created = 0;

	break;

      case M_MAILDIR:

	snprintf (path, sizeof (path), "%s/new", tmp->path);
	if ((dirp = opendir (path)) == NULL)
	{
	  tmp->magic = 0;
	  break;
	}
	while ((de = readdir (dirp)) != NULL)
	{
	  char *p;
	  if (*de->d_name != '.' && 
	      (!(p = strstr (de->d_name, ":2,")) || !strchr (p + 3, 'T')))
	  {
	    /* one new and undeleted message is enough */
	    BuffyCount++;
	    tmp->new = 1;
	    break;
	  }
	}
	closedir (dirp);
	break;

      case M_MH:
	if ((tmp->new = mh_buffy (tmp->path)) > 0)
	  BuffyCount++;
	break;
	
#ifdef USE_IMAP
      case M_IMAP:
	if ((tmp->new = imap_mailbox_check (tmp->path, 1)) > 0)
	  BuffyCount++;
	else
	  tmp->new = 0;

	break;
#endif

#ifdef USE_POP
      case M_POP:
	break;
#endif
      }
    }
#ifdef BUFFY_SIZE
    else if (Context && Context->path)
      tmp->size = (long) sb.st_size;	/* update the size */
#endif

    if (!tmp->new)
      tmp->notified = 0;
    else if (!tmp->notified)
      BuffyNotify++;
  }

  BuffyDoneTime = BuffyTime;
  return (BuffyCount);
}