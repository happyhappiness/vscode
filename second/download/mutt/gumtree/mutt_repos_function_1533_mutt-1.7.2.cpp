static int mh_check_mailbox (CONTEXT * ctx, int *index_hint)
{
  char buf[_POSIX_PATH_MAX];
  struct stat st, st_cur;
  short modified = 0, have_new = 0, occult = 0;
  struct maildir *md, *p;
  struct maildir **last = NULL;
  struct mh_sequences mhs;
  HASH *fnames;
  int i;
  struct mh_data *data = mh_data (ctx);

  if (!option (OPTCHECKNEW))
    return 0;

  strfcpy (buf, ctx->path, sizeof (buf));
  if (stat (buf, &st) == -1)
    return -1;
  
  /* create .mh_sequences when there isn't one. */
  snprintf (buf, sizeof (buf), "%s/.mh_sequences", ctx->path);
  if ((i = stat (buf, &st_cur)) == -1 && errno == ENOENT)
  {
    char *tmp;
    FILE *fp = NULL;
    
    if (mh_mkstemp (ctx, &fp, &tmp) == 0)
    {
      safe_fclose (&fp);
      if (safe_rename (tmp, buf) == -1)
	unlink (tmp);
      FREE (&tmp);
    }
  }

  if (i == -1 && stat (buf, &st_cur) == -1)
    modified = 1;

  if (st.st_mtime > ctx->mtime || st_cur.st_mtime > data->mtime_cur)
    modified = 1;

  if (!modified)
    return 0;

  data->mtime_cur = st_cur.st_mtime;
  ctx->mtime = st.st_mtime;

  memset (&mhs, 0, sizeof (mhs));

  md   = NULL;
  last = &md;

  maildir_parse_dir (ctx, &last, NULL, NULL, NULL);
  maildir_delayed_parsing (ctx, &md, NULL);

  if (mh_read_sequences (&mhs, ctx->path) < 0)
    return -1;
  mh_update_maildir (md, &mhs);
  mhs_free_sequences (&mhs);

  /* check for modifications and adjust flags */
  fnames = hash_create (1031, 0);

  for (p = md; p; p = p->next)
  {
    /* the hash key must survive past the header, which is freed below. */
    p->canon_fname = safe_strdup (p->h->path);
    hash_insert (fnames, p->canon_fname, p, 0);
  }

  for (i = 0; i < ctx->msgcount; i++)
  {
    ctx->hdrs[i]->active = 0;

    if ((p = hash_find (fnames, ctx->hdrs[i]->path)) && p->h &&
	(mbox_strict_cmp_headers (ctx->hdrs[i], p->h)))
    {
      ctx->hdrs[i]->active = 1;
      /* found the right message */
      if (!ctx->hdrs[i]->changed)
	maildir_update_flags (ctx, ctx->hdrs[i], p->h);

      mutt_free_header (&p->h);
    }
    else /* message has disappeared */
      occult = 1;
  }

  /* destroy the file name hash */

  hash_destroy (&fnames, NULL);

  /* If we didn't just get new mail, update the tables. */
  if (occult)
    maildir_update_tables (ctx, index_hint);

  /* Incorporate new messages */
  have_new = maildir_move_to_context (ctx, &md);

  return occult ? MUTT_REOPENED : (have_new ? MUTT_NEW_MAIL : 0);
}