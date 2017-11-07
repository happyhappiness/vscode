int mbox_sync_mailbox (CONTEXT *ctx, int *index_hint)
{
  char tempfile[_POSIX_PATH_MAX];
  char buf[32];
  int i, j, save_sort = SORT_ORDER;
  int rc = -1;
  int need_sort = 0; /* flag to resort mailbox if new mail arrives */
  int first = -1;	/* first message to be written */
  LOFF_T offset;	/* location in mailbox to write changed messages */
  struct stat statbuf;
  struct m_update_t *newOffset = NULL;
  struct m_update_t *oldOffset = NULL;
  FILE *fp = NULL;
  progress_t progress;
  char msgbuf[STRING];

  /* sort message by their position in the mailbox on disk */
  if (Sort != SORT_ORDER)
  {
    save_sort = Sort;
    Sort = SORT_ORDER;
    mutt_sort_headers (ctx, 0);
    Sort = save_sort;
    need_sort = 1;
  }

  /* need to open the file for writing in such a way that it does not truncate
   * the file, so use read-write mode.
   */
  if ((ctx->fp = freopen (ctx->path, "r+", ctx->fp)) == NULL)
  {
    mx_fastclose_mailbox (ctx);
    mutt_error _("Fatal error!  Could not reopen mailbox!");
    return (-1);
  }

  mutt_block_signals ();

  if (mbox_lock_mailbox (ctx, 1, 1) == -1)
  {
    mutt_unblock_signals ();
    mutt_error _("Unable to lock mailbox!");
    goto bail;
  }

  /* Check to make sure that the file hasn't changed on disk */
  if ((i = mbox_check_mailbox (ctx, index_hint)) == MUTT_NEW_MAIL ||  i == MUTT_REOPENED)
  {
    /* new mail arrived, or mailbox reopened */
    need_sort = i;
    rc = i;
    goto bail;
  }
  else if (i < 0)
    /* fatal error */
    return (-1);

  /* Create a temporary file to write the new version of the mailbox in. */
  mutt_mktemp (tempfile, sizeof (tempfile));
  if ((i = open (tempfile, O_WRONLY | O_EXCL | O_CREAT, 0600)) == -1 ||
      (fp = fdopen (i, "w")) == NULL)
  {
    if (-1 != i)
    {
      close (i);
      unlink (tempfile);
    }
    mutt_error _("Could not create temporary file!");
    mutt_sleep (5);
    goto bail;
  }

  /* find the first deleted/changed message.  we save a lot of time by only
   * rewriting the mailbox from the point where it has actually changed.
   */
  for (i = 0 ; i < ctx->msgcount && !ctx->hdrs[i]->deleted && 
               !ctx->hdrs[i]->changed && !ctx->hdrs[i]->attach_del; i++)
    ;
  if (i == ctx->msgcount)
  { 
    /* this means ctx->changed or ctx->deleted was set, but no
     * messages were found to be changed or deleted.  This should
     * never happen, is we presume it is a bug in mutt.
     */
    mutt_error _("sync: mbox modified, but no modified messages! (report this bug)");
    mutt_sleep(5); /* the mutt_error /will/ get cleared! */
    dprint(1, (debugfile, "mbox_sync_mailbox(): no modified messages.\n"));
    unlink (tempfile);
    goto bail;
  }

    /* save the index of the first changed/deleted message */
  first = i; 
  /* where to start overwriting */
  offset = ctx->hdrs[i]->offset; 

  /* the offset stored in the header does not include the MMDF_SEP, so make
   * sure we seek to the correct location
   */
  if (ctx->magic == MUTT_MMDF)
    offset -= (sizeof MMDF_SEP - 1);
  
  /* allocate space for the new offsets */
  newOffset = safe_calloc (ctx->msgcount - first, sizeof (struct m_update_t));
  oldOffset = safe_calloc (ctx->msgcount - first, sizeof (struct m_update_t));

  if (!ctx->quiet)
  {
    snprintf (msgbuf, sizeof (msgbuf), _("Writing %s..."), ctx->path);
    mutt_progress_init (&progress, msgbuf, MUTT_PROGRESS_MSG, WriteInc, ctx->msgcount);
  }

  for (i = first, j = 0; i < ctx->msgcount; i++)
  {
    if (!ctx->quiet)
      mutt_progress_update (&progress, i, (int)(ftello (ctx->fp) / (ctx->size / 100 + 1)));
    /*
     * back up some information which is needed to restore offsets when
     * something fails.
     */
    
    oldOffset[i-first].valid  = 1;
    oldOffset[i-first].hdr    = ctx->hdrs[i]->offset;
    oldOffset[i-first].body   = ctx->hdrs[i]->content->offset;
    oldOffset[i-first].lines  = ctx->hdrs[i]->lines;
    oldOffset[i-first].length = ctx->hdrs[i]->content->length;

    if (! ctx->hdrs[i]->deleted)
    {
      j++;

      if (ctx->magic == MUTT_MMDF)
      {
	if (fputs (MMDF_SEP, fp) == EOF)
	{
	  mutt_perror (tempfile);
	  mutt_sleep (5);
	  unlink (tempfile);
	  goto bail;
	}
	  
      }

      /* save the new offset for this message.  we add `offset' because the
       * temporary file only contains saved message which are located after
       * `offset' in the real mailbox
       */
      newOffset[i - first].hdr = ftello (fp) + offset;

      if (mutt_copy_message (fp, ctx, ctx->hdrs[i], MUTT_CM_UPDATE,
                             CH_FROM | CH_UPDATE | CH_UPDATE_LEN) != 0)
      {
	mutt_perror (tempfile);
	mutt_sleep (5);
	unlink (tempfile);
	goto bail;
      }

      /* Since messages could have been deleted, the offsets stored in memory
       * will be wrong, so update what we can, which is the offset of this
       * message, and the offset of the body.  If this is a multipart message,
       * we just flush the in memory cache so that the message will be reparsed
       * if the user accesses it later.
       */
      newOffset[i - first].body = ftello (fp) - ctx->hdrs[i]->content->length + offset;
      mutt_free_body (&ctx->hdrs[i]->content->parts);

      switch(ctx->magic)
      {
	case MUTT_MMDF: 
	  if(fputs(MMDF_SEP, fp) == EOF) 
	  {
	    mutt_perror (tempfile);
	    mutt_sleep (5);
	    unlink (tempfile);
	    goto bail; 
	  }
	  break;
	default:
	  if(fputs("\n", fp) == EOF) 
	  {
	    mutt_perror (tempfile);
	    mutt_sleep (5);
	    unlink (tempfile);
	    goto bail;
	  }
      }
    }
  }
  
  if (fclose (fp) != 0)
  {
    fp = NULL;
    dprint(1, (debugfile, "mbox_sync_mailbox: safe_fclose (&) returned non-zero.\n"));
    unlink (tempfile);
    mutt_perror (tempfile);
    mutt_sleep (5);
    goto bail;
  }
  fp = NULL;

  /* Save the state of this folder. */
  if (stat (ctx->path, &statbuf) == -1)
  {
    mutt_perror (ctx->path);
    mutt_sleep (5);
    unlink (tempfile);
    goto bail;
  }

  if ((fp = fopen (tempfile, "r")) == NULL)
  {
    mutt_unblock_signals ();
    mx_fastclose_mailbox (ctx);
    dprint (1, (debugfile, "mbox_sync_mailbox: unable to reopen temp copy of mailbox!\n"));
    mutt_perror (tempfile);
    mutt_sleep (5);
    return (-1);
  }

  if (fseeko (ctx->fp, offset, SEEK_SET) != 0 ||  /* seek the append location */
      /* do a sanity check to make sure the mailbox looks ok */
      fgets (buf, sizeof (buf), ctx->fp) == NULL ||
      (ctx->magic == MUTT_MBOX && mutt_strncmp ("From ", buf, 5) != 0) ||
      (ctx->magic == MUTT_MMDF && mutt_strcmp (MMDF_SEP, buf) != 0))
  {
    dprint (1, (debugfile, "mbox_sync_mailbox: message not in expected position."));
    dprint (1, (debugfile, "\tLINE: %s\n", buf));
    i = -1;
  }
  else
  {
    if (fseeko (ctx->fp, offset, SEEK_SET) != 0) /* return to proper offset */
    {
      i = -1;
      dprint (1, (debugfile, "mbox_sync_mailbox: fseek() failed\n"));
    }
    else
    {
      /* copy the temp mailbox back into place starting at the first
       * change/deleted message
       */
      if (!ctx->quiet)
	mutt_message _("Committing changes...");
      i = mutt_copy_stream (fp, ctx->fp);

      if (ferror (ctx->fp))
        i = -1;
    }
    if (i == 0)
    {
      ctx->size = ftello (ctx->fp); /* update the size of the mailbox */
      if (ftruncate (fileno (ctx->fp), ctx->size) != 0)
      {
        i = -1;
        dprint (1, (debugfile, "mbox_sync_mailbox: ftruncate() failed\n"));
      }
    }
  }

  safe_fclose (&fp);
  fp = NULL;
  mbox_unlock_mailbox (ctx);

  if (safe_fclose (&ctx->fp) != 0 || i == -1)
  {
    /* error occurred while writing the mailbox back, so keep the temp copy
     * around
     */
    
    char savefile[_POSIX_PATH_MAX];
    
    snprintf (savefile, sizeof (savefile), "%s/mutt.%s-%s-%u",
	      NONULL (Tempdir), NONULL(Username), NONULL(Hostname), (unsigned int)getpid ());
    rename (tempfile, savefile);
    mutt_unblock_signals ();
    mx_fastclose_mailbox (ctx);
    mutt_pretty_mailbox (savefile, sizeof (savefile));
    mutt_error (_("Write failed!  Saved partial mailbox to %s"), savefile);
    mutt_sleep (5);
    return (-1);
  }

  /* Restore the previous access/modification times */
  mbox_reset_atime (ctx, &statbuf);

  /* reopen the mailbox in read-only mode */
  if ((ctx->fp = fopen (ctx->path, "r")) == NULL)
  {
    unlink (tempfile);
    mutt_unblock_signals ();
    mx_fastclose_mailbox (ctx);
    mutt_error _("Fatal error!  Could not reopen mailbox!");
    return (-1);
  }

  /* update the offsets of the rewritten messages */
  for (i = first, j = first; i < ctx->msgcount; i++)
  {
    if (!ctx->hdrs[i]->deleted)
    {
      ctx->hdrs[i]->offset = newOffset[i - first].hdr;
      ctx->hdrs[i]->content->hdr_offset = newOffset[i - first].hdr;
      ctx->hdrs[i]->content->offset = newOffset[i - first].body;
      ctx->hdrs[i]->index = j++;
    }
  }
  FREE (&newOffset);
  FREE (&oldOffset);
  unlink (tempfile); /* remove partial copy of the mailbox */
  mutt_unblock_signals ();

  return (0); /* signal success */

bail:  /* Come here in case of disaster */

  safe_fclose (&fp);

  /* restore offsets, as far as they are valid */
  if (first >= 0 && oldOffset)
  {
    for (i = first; i < ctx->msgcount && oldOffset[i-first].valid; i++)
    {
      ctx->hdrs[i]->offset = oldOffset[i-first].hdr;
      ctx->hdrs[i]->content->hdr_offset = oldOffset[i-first].hdr;
      ctx->hdrs[i]->content->offset = oldOffset[i-first].body;
      ctx->hdrs[i]->lines = oldOffset[i-first].lines;
      ctx->hdrs[i]->content->length = oldOffset[i-first].length;
    }
  }
  
  /* this is ok to call even if we haven't locked anything */
  mbox_unlock_mailbox (ctx);

  mutt_unblock_signals ();
  FREE (&newOffset);
  FREE (&oldOffset);

  if ((ctx->fp = freopen (ctx->path, "r", ctx->fp)) == NULL)
  {
    mutt_error _("Could not reopen mailbox!");
    mx_fastclose_mailbox (ctx);
    return (-1);
  }

  if (need_sort)
    /* if the mailbox was reopened, the thread tree will be invalid so make
     * sure to start threading from scratch.  */
    mutt_sort_headers (ctx, (need_sort == MUTT_REOPENED));

  return rc;
}