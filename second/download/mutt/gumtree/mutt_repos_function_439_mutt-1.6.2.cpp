int mutt_buffy_check (int force)
{
  BUFFY *tmp;
  struct stat sb;
  struct stat contex_sb;
  time_t t;

  sb.st_size=0;
  contex_sb.st_dev=0;
  contex_sb.st_ino=0;

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
  BuffyCount += imap_buffy_check (force);
#endif

  /* check device ID and serial number instead of comparing paths */
  if (!Context || Context->magic == M_IMAP || Context->magic == M_POP
      || stat (Context->path, &contex_sb) != 0)
  {
    contex_sb.st_dev=0;
    contex_sb.st_ino=0;
  }
  
  for (tmp = Incoming; tmp; tmp = tmp->next)
  {
    if (tmp->magic != M_IMAP)
    {
      tmp->new = 0;
#ifdef USE_POP
      if (mx_is_pop (tmp->path))
	tmp->magic = M_POP;
      else
#endif
      if (stat (tmp->path, &sb) != 0 || (S_ISREG(sb.st_mode) && sb.st_size == 0) ||
	  (!tmp->magic && (tmp->magic = mx_get_magic (tmp->path)) <= 0))
      {
	/* if the mailbox still doesn't exist, set the newly created flag to
	 * be ready for when it does. */
	tmp->newly_created = 1;
	tmp->magic = 0;
	tmp->size = 0;
	continue;
      }
    }

    /* check to see if the folder is the currently selected folder
     * before polling */
    if (!Context || !Context->path ||
	(( tmp->magic == M_IMAP || tmp->magic == M_POP )
	    ? mutt_strcmp (tmp->path, Context->path) :
	      (sb.st_dev != contex_sb.st_dev || sb.st_ino != contex_sb.st_ino)))
    {
      switch (tmp->magic)
      {
      case M_MBOX:
      case M_MMDF:
	if (buffy_mbox_hasnew (tmp, &sb) > 0)
	  BuffyCount++;
	break;

      case M_MAILDIR:
	if (buffy_maildir_hasnew (tmp) > 0)
	  BuffyCount++;
	break;

      case M_MH:
	mh_buffy(tmp);
	if (tmp->new)
	  BuffyCount++;
	break;
      }
    }
    else if (option(OPTCHECKMBOXSIZE) && Context && Context->path)
      tmp->size = (off_t) sb.st_size;	/* update the size of current folder */

    if (!tmp->new)
      tmp->notified = 0;
    else if (!tmp->notified)
      BuffyNotify++;
  }

  BuffyDoneTime = BuffyTime;
  return (BuffyCount);
}