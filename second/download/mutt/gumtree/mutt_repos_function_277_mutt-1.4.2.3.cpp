int mutt_parse_mailboxes (BUFFER *path, BUFFER *s, unsigned long data, BUFFER *err)
{
  BUFFY **tmp;
  char buf[_POSIX_PATH_MAX];
#ifdef BUFFY_SIZE
  struct stat sb;
#endif /* BUFFY_SIZE */

  while (MoreArgs (s))
  {
    mutt_extract_token (path, s, 0);
    strfcpy (buf, path->data, sizeof (buf));
    mutt_expand_path (buf, sizeof (buf));

    /* Skip empty tokens. */
    if(!*buf) continue;

    /* simple check to avoid duplicates */
    for (tmp = &Incoming; *tmp; tmp = &((*tmp)->next))
    {
      if (mutt_strcmp (buf, (*tmp)->path) == 0)
	break;
    }

    if (!*tmp)
    {
      *tmp = (BUFFY *) safe_calloc (1, sizeof (BUFFY));
      (*tmp)->path = safe_strdup (buf);
      (*tmp)->next = NULL;
      /* it is tempting to set magic right here */
      (*tmp)->magic = 0;
      
    }

    (*tmp)->new = 0;
    (*tmp)->notified = 1;
    (*tmp)->newly_created = 0;

#ifdef BUFFY_SIZE
    /* for buffy_size, it is important that if the folder is new (tested by
     * reading it), the size is set to 0 so that later when we check we see
     * that it increased .  without buffy_size we probably don't care.
     */
    if (stat ((*tmp)->path, &sb) == 0 && !test_new_folder ((*tmp)->path))
    {
      /* some systems out there don't have an off_t type */
      (*tmp)->size = (long) sb.st_size;
    }
    else
      (*tmp)->size = 0;
#endif /* BUFFY_SIZE */
  }
  return 0;
}