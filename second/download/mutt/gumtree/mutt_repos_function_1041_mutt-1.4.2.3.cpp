int mh_check_mailbox(CONTEXT *ctx, int *index_hint)
{
  char buf[_POSIX_PATH_MAX], b1[LONG_STRING], b2[LONG_STRING];
  struct stat st, st_cur;
  short modified = 0, have_new = 0, occult = 0;
  struct maildir *md, *p;
  struct maildir **last;
  HASH *fnames;
  int i, j;
  
  if(!option (OPTCHECKNEW))
    return 0;
  
  if(ctx->magic == M_MH)
  {
    strfcpy(buf, ctx->path, sizeof(buf));
    if(stat(buf, &st) == -1)
      return -1;

    /* create .mh_sequences when there isn't one. */
    snprintf (buf, sizeof (buf), "%s/.mh_sequences", ctx->path);
    if (stat (buf, &st_cur) == -1)
    {
      if (errno == ENOENT)
      {
	char *tmp;
	FILE *fp = NULL;

	if (mh_mkstemp (ctx, &fp, &tmp) == 0)
	{
	  safe_fclose (&fp);
	  if (safe_rename (tmp, buf) == -1)
	    unlink (tmp);
	  safe_free ((void **) &tmp);
	}
	
	if (stat (buf, &st_cur) == -1)
	  modified = 1;
      }
      else
	modified = 1;
    }
  }
  else if(ctx->magic == M_MAILDIR)
  {
    snprintf(buf, sizeof(buf), "%s/new", ctx->path);
    if(stat(buf, &st) == -1)
      return -1;
    
    snprintf(buf, sizeof(buf), "%s/cur", ctx->path);
    if(stat(buf, &st_cur) == -1)			/* XXX - name is bad. */
      modified = 1;

  }
  
  if(!modified && ctx->magic == M_MAILDIR && st_cur.st_mtime > ctx->mtime_cur)
    modified = 1;
  
  if(!modified && ctx->magic == M_MH && (st.st_mtime > ctx->mtime || st_cur.st_mtime > ctx->mtime_cur))
    modified = 1;
  
  if(modified || (ctx->magic == M_MAILDIR && st.st_mtime > ctx->mtime))
    have_new = 1;
  
  if(!modified && !have_new)
    return 0;

  ctx->mtime_cur = st_cur.st_mtime;
  ctx->mtime = st.st_mtime;

#if 0
  if(Sort != SORT_ORDER)
  {
    short old_sort;
    
    old_sort = Sort;
    Sort = SORT_ORDER;
    mutt_sort_headers(ctx, 1);
    Sort = old_sort;
  }
#endif

  md = NULL;
  last = &md;

  if(ctx->magic == M_MAILDIR)
  {
    if(have_new)
      maildir_parse_dir(ctx, &last, "new", NULL);
    if(modified)
      maildir_parse_dir(ctx, &last, "cur", NULL);
  }
  else if(ctx->magic == M_MH)
  {
    struct mh_sequences mhs;
    memset (&mhs, 0, sizeof (mhs));
    maildir_parse_dir (ctx, &last, NULL, NULL);
    mh_read_sequences (&mhs, ctx->path);
    mh_update_maildir (md, &mhs);
    mhs_free_sequences (&mhs);
  }

  /* check for modifications and adjust flags */

  fnames = hash_create (1031);
  
  for(p = md; p; p = p->next)
  {
    if(ctx->magic == M_MAILDIR)
    {
      maildir_canon_filename(b2, p->h->path, sizeof(b2));
      p->canon_fname = safe_strdup(b2);
    }
    else
      p->canon_fname = safe_strdup(p->h->path);
    
    hash_insert(fnames, p->canon_fname, p, 0);
  }

  
  for(i = 0; i < ctx->msgcount; i++)
  {
    ctx->hdrs[i]->active = 0;

    if(ctx->magic == M_MAILDIR)
      maildir_canon_filename(b1, ctx->hdrs[i]->path, sizeof(b1));
    else
      strfcpy(b1, ctx->hdrs[i]->path, sizeof(b1));

    dprint(2, (debugfile, "%s:%d: mh_check_mailbox(): Looking for %s.\n", __FILE__, __LINE__, b1));
    
    if((p = hash_find(fnames, b1)) && p->h &&
       mbox_strict_cmp_headers(ctx->hdrs[i], p->h))
    {
      /* found the right message */

      dprint(2, (debugfile, "%s:%d: Found.  Flags before: %s%s%s%s%s\n", __FILE__, __LINE__,
		 ctx->hdrs[i]->flagged ? "f" : "",
		 ctx->hdrs[i]->deleted ? "D" : "",
		 ctx->hdrs[i]->replied ? "r" : "",
		 ctx->hdrs[i]->old     ? "O" : "",
		 ctx->hdrs[i]->read    ? "R" : ""));

      if(mutt_strcmp(ctx->hdrs[i]->path, p->h->path))
	mutt_str_replace (&ctx->hdrs[i]->path, p->h->path);

      if(modified)
      {
	if(!ctx->hdrs[i]->changed)
	{
	  mutt_set_flag (ctx, ctx->hdrs[i], M_FLAG, p->h->flagged);
	  mutt_set_flag (ctx, ctx->hdrs[i], M_REPLIED, p->h->replied);
	  mutt_set_flag (ctx, ctx->hdrs[i], M_READ, p->h->read);
	}

	mutt_set_flag(ctx, ctx->hdrs[i], M_OLD, p->h->old);
      }

      ctx->hdrs[i]->active = 1;

      dprint(2, (debugfile, "%s:%d:         Flags after: %s%s%s%s%s\n", __FILE__, __LINE__,
		 ctx->hdrs[i]->flagged ? "f" : "",
		 ctx->hdrs[i]->deleted ? "D" : "",
		 ctx->hdrs[i]->replied ? "r" : "",
		 ctx->hdrs[i]->old     ? "O" : "",
		 ctx->hdrs[i]->read    ? "R" : ""));

      mutt_free_header(&p->h);
    }
    else if (ctx->magic == M_MAILDIR && !modified && !strncmp("cur/", ctx->hdrs[i]->path, 4))
    {
      /* If the cur/ part wasn't externally modified for a maildir
       * type folder, assume the message is still active. Actually,
       * we simply don't know.
       */

      ctx->hdrs[i]->active = 1;
    }
    else if (modified || (ctx->magic == M_MAILDIR && !strncmp("new/", ctx->hdrs[i]->path, 4)))
    {
      
      /* Mailbox was modified, or a new message vanished. */

      /* Note: This code will _not_ apply for a new message which
       * is just moved to cur/, as this would modify cur's time
       * stamp and lead to modified == 1.  Thus, we'd have parsed
       * the complete folder above, and the message would have
       * been found in the look-up table.
       */
      
      dprint(2, (debugfile, "%s:%d: Not found.  Flags were: %s%s%s%s%s\n", __FILE__, __LINE__,
		 ctx->hdrs[i]->flagged ? "f" : "",
		 ctx->hdrs[i]->deleted ? "D" : "",
		 ctx->hdrs[i]->replied ? "r" : "",
		 ctx->hdrs[i]->old     ? "O" : "",
		 ctx->hdrs[i]->read    ? "R" : ""));
      
      occult = 1;

    }
  }

  /* destroy the file name hash */

  hash_destroy(&fnames, NULL);

  /* If we didn't just get new mail, update the tables. */
  
  if(modified || occult)
  {
    short old_sort;
    int old_count;

    if (Sort != SORT_ORDER)
    {
      old_sort = Sort;
      Sort = SORT_ORDER;
      mutt_sort_headers (ctx, 1);
      Sort = old_sort;
    }
  
    old_count = ctx->msgcount;
    for (i = 0, j = 0; i < old_count; i++)
    {
      if (ctx->hdrs[i]->active && index_hint && *index_hint == i)
	*index_hint = j;

      if (ctx->hdrs[i]->active)
	ctx->hdrs[i]->index = j++;
    }
    mx_update_tables(ctx, 0);
  }

  /* Incorporate new messages */

  maildir_move_to_context(ctx, &md);

  return (modified || occult) ? M_REOPENED : have_new ? M_NEW_MAIL : 0;
}