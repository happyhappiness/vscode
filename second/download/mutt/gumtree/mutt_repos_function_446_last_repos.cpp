int mutt_parse_mailboxes (BUFFER *path, BUFFER *s, unsigned long data, BUFFER *err)
{
  BUFFY **tmp,*tmp1;
  char buf[_POSIX_PATH_MAX];
  struct stat sb;
  char f1[PATH_MAX];
  char *p;

  while (MoreArgs (s))
  {
    mutt_extract_token (path, s, 0);
    strfcpy (buf, path->data, sizeof (buf));

    if(data == MUTT_UNMAILBOXES && mutt_strcmp(buf,"*") == 0)
    {
      for (tmp = &Incoming; *tmp;)
      {
        tmp1=(*tmp)->next;
#ifdef USE_SIDEBAR
	mutt_sb_notify_mailbox (*tmp, 0);
#endif
        buffy_free (tmp);
        *tmp=tmp1;
      }
      return 0;
    }

    mutt_expand_path (buf, sizeof (buf));

    /* Skip empty tokens. */
    if(!*buf) continue;

    /* avoid duplicates */
    p = realpath (buf, f1);
    for (tmp = &Incoming; *tmp; tmp = &((*tmp)->next))
    {
      if (mutt_strcmp (p ? p : buf, (*tmp)->realpath) == 0)
      {
	dprint(3,(debugfile,"mailbox '%s' already registered as '%s'\n", buf, (*tmp)->path));
	break;
      }
    }

    if(data == MUTT_UNMAILBOXES)
    {
      if(*tmp)
      {
        tmp1=(*tmp)->next;
#ifdef USE_SIDEBAR
	mutt_sb_notify_mailbox (*tmp, 0);
#endif
        buffy_free (tmp);
        *tmp=tmp1;
      }
      continue;
    }

    if (!*tmp) {
      *tmp = buffy_new (buf);
#ifdef USE_SIDEBAR
      mutt_sb_notify_mailbox (*tmp, 1);
#endif
    }

    (*tmp)->new = 0;
    (*tmp)->notified = 1;
    (*tmp)->newly_created = 0;

    /* for check_mbox_size, it is important that if the folder is new (tested by
     * reading it), the size is set to 0 so that later when we check we see
     * that it increased .  without check_mbox_size we probably don't care.
     */
    if (option(OPTCHECKMBOXSIZE) &&
	stat ((*tmp)->path, &sb) == 0 && !test_new_folder ((*tmp)->path))
    {
      /* some systems out there don't have an off_t type */
      (*tmp)->size = (off_t) sb.st_size;
    }
    else
      (*tmp)->size = 0;
  }
  return 0;
}