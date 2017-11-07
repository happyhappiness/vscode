static int maildir_check_mailbox (CONTEXT * ctx, int *index_hint)
{
  struct stat st_new;		/* status of the "new" subdirectory */
  struct stat st_cur;		/* status of the "cur" subdirectory */
  char buf[_POSIX_PATH_MAX];
  int changed = 0;		/* bitmask representing which subdirectories
				   have changed.  0x1 = new, 0x2 = cur */
  int occult = 0;		/* messages were removed from the mailbox */
  int have_new = 0;		/* messages were added to the mailbox */
  struct maildir *md;		/* list of messages in the mailbox */
  struct maildir **last, *p;
  int i;
  HASH *fnames;			/* hash table for quickly looking up the base filename
				   for a maildir message */
  struct mh_data *data = mh_data (ctx);

  /* XXX seems like this check belongs in mx_check_mailbox()
   * rather than here.
   */
  if (!option (OPTCHECKNEW))
    return 0;

  snprintf (buf, sizeof (buf), "%s/new", ctx->path);
  if (stat (buf, &st_new) == -1)
    return -1;

  snprintf (buf, sizeof (buf), "%s/cur", ctx->path);
  if (stat (buf, &st_cur) == -1)
    return -1;

  /* determine which subdirectories need to be scanned */
  if (st_new.st_mtime > ctx->mtime)
    changed = 1;
  if (st_cur.st_mtime > data->mtime_cur)
    changed |= 2;

  if (!changed)
    return 0;			/* nothing to do */

  /* update the modification times on the mailbox */
  data->mtime_cur = st_cur.st_mtime;
  ctx->mtime = st_new.st_mtime;

  /* do a fast scan of just the filenames in
   * the subdirectories that have changed.
   */
  md = NULL;
  last = &md;
  if (changed & 1)
    maildir_parse_dir (ctx, &last, "new", NULL, NULL);
  if (changed & 2)
    maildir_parse_dir (ctx, &last, "cur", NULL, NULL);

  /* we create a hash table keyed off the canonical (sans flags) filename
   * of each message we scanned.  This is used in the loop over the
   * existing messages below to do some correlation.
   */
  fnames = hash_create (1031, 0);

  for (p = md; p; p = p->next)
  {
    maildir_canon_filename (buf, p->h->path, sizeof (buf));
    p->canon_fname = safe_strdup (buf);
    hash_insert (fnames, p->canon_fname, p, 0);
  }

  /* check for modifications and adjust flags */
  for (i = 0; i < ctx->msgcount; i++)
  {
    ctx->hdrs[i]->active = 0;
    maildir_canon_filename (buf, ctx->hdrs[i]->path, sizeof (buf));
    p = hash_find (fnames, buf);
    if (p && p->h)
    {
      /* message already exists, merge flags */
      ctx->hdrs[i]->active = 1;

      /* check to see if the message has moved to a different
       * subdirectory.  If so, update the associated filename.
       */
      if (mutt_strcmp (ctx->hdrs[i]->path, p->h->path))
	mutt_str_replace (&ctx->hdrs[i]->path, p->h->path);

      /* if the user hasn't modified the flags on this message, update
       * the flags we just detected.
       */
      if (!ctx->hdrs[i]->changed)
	maildir_update_flags (ctx, ctx->hdrs[i], p->h);

      if (ctx->hdrs[i]->deleted == ctx->hdrs[i]->trash)
	ctx->hdrs[i]->deleted = p->h->deleted;
      ctx->hdrs[i]->trash = p->h->trash;

      /* this is a duplicate of an existing header, so remove it */
      mutt_free_header (&p->h);
    }
    /* This message was not in the list of messages we just scanned.
     * Check to see if we have enough information to know if the
     * message has disappeared out from underneath us.
     */
    else if (((changed & 1) && (!strncmp (ctx->hdrs[i]->path, "new/", 4))) ||
	     ((changed & 2) && (!strncmp (ctx->hdrs[i]->path, "cur/", 4))))
    {
      /* This message disappeared, so we need to simulate a "reopen"
       * event.  We know it disappeared because we just scanned the
       * subdirectory it used to reside in.
       */
      occult = 1;
    }
    else
    {
      /* This message resides in a subdirectory which was not
       * modified, so we assume that it is still present and
       * unchanged.
       */
      ctx->hdrs[i]->active = 1;
    }
  }

  /* destroy the file name hash */
  hash_destroy (&fnames, NULL);

  /* If we didn't just get new mail, update the tables. */
  if (occult)
    maildir_update_tables (ctx, index_hint);
  
  /* do any delayed parsing we need to do. */
  maildir_delayed_parsing (ctx, &md, NULL);

  /* Incorporate new messages */
  have_new = maildir_move_to_context (ctx, &md);

  return occult ? MUTT_REOPENED : (have_new ? MUTT_NEW_MAIL : 0);
}