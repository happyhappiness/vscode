int mbox_parse_mailbox (CONTEXT *ctx)
{
  struct stat sb;
  char buf[HUGE_STRING], return_path[STRING];
  HEADER *curhdr;
  time_t t;
  int count = 0, lines = 0;
  LOFF_T loc;
#ifdef NFS_ATTRIBUTE_HACK
  struct utimbuf newtime;
#endif
  progress_t progress;
  char msgbuf[STRING];

  /* Save information about the folder at the time we opened it. */
  if (stat (ctx->path, &sb) == -1)
  {
    mutt_perror (ctx->path);
    return (-1);
  }

  ctx->size = sb.st_size;
  ctx->mtime = sb.st_mtime;
  ctx->atime = sb.st_atime;

#ifdef NFS_ATTRIBUTE_HACK
  if (sb.st_mtime > sb.st_atime)
  {
    newtime.modtime = sb.st_mtime;
    newtime.actime = time (NULL);
    utime (ctx->path, &newtime);
  }
#endif

  if (!ctx->readonly)
    ctx->readonly = access (ctx->path, W_OK) ? 1 : 0;

  if (!ctx->quiet)
  {
    snprintf (msgbuf, sizeof (msgbuf), _("Reading %s..."), ctx->path);
    mutt_progress_init (&progress, msgbuf, MUTT_PROGRESS_MSG, ReadInc, 0);
  }

  loc = ftello (ctx->fp);
  while (fgets (buf, sizeof (buf), ctx->fp) != NULL)
  {
    if (is_from (buf, return_path, sizeof (return_path), &t))
    {
      /* Save the Content-Length of the previous message */
      if (count > 0)
      {
#define PREV ctx->hdrs[ctx->msgcount-1]

	if (PREV->content->length < 0)
	{
	  PREV->content->length = loc - PREV->content->offset - 1;
	  if (PREV->content->length < 0)
	    PREV->content->length = 0;
	}
	if (!PREV->lines)
	  PREV->lines = lines ? lines - 1 : 0;
      }

      count++;

      if (!ctx->quiet)
	mutt_progress_update (&progress, count,
			      (int)(ftello (ctx->fp) / (ctx->size / 100 + 1)));

      if (ctx->msgcount == ctx->hdrmax)
	mx_alloc_memory (ctx);
      
      curhdr = ctx->hdrs[ctx->msgcount] = mutt_new_header ();
      curhdr->received = t - mutt_local_tz (t);
      curhdr->offset = loc;
      curhdr->index = ctx->msgcount;
	
      curhdr->env = mutt_read_rfc822_header (ctx->fp, curhdr, 0, 0);

      /* if we know how long this message is, either just skip over the body,
       * or if we don't know how many lines there are, count them now (this will
       * save time by not having to search for the next message marker).
       */
      if (curhdr->content->length > 0)
      {
	LOFF_T tmploc;

	loc = ftello (ctx->fp);
	tmploc = loc + curhdr->content->length + 1;

	if (0 < tmploc && tmploc < ctx->size)
	{
	  /*
	   * check to see if the content-length looks valid.  we expect to
	   * to see a valid message separator at this point in the stream
	   */
	  if (fseeko (ctx->fp, tmploc, SEEK_SET) != 0 ||
	      fgets (buf, sizeof (buf), ctx->fp) == NULL ||
	      mutt_strncmp ("From ", buf, 5) != 0)
	  {
	    dprint (1, (debugfile, "mbox_parse_mailbox: bad content-length in message %d (cl=" OFF_T_FMT ")\n", curhdr->index, curhdr->content->length));
	    dprint (1, (debugfile, "\tLINE: %s", buf));
	    if (fseeko (ctx->fp, loc, SEEK_SET) != 0) /* nope, return the previous position */
	    {
	      dprint (1, (debugfile, "mbox_parse_mailbox: fseek() failed\n"));
	    }
	    curhdr->content->length = -1;
	  }
	}
	else if (tmploc != ctx->size)
	{
	  /* content-length would put us past the end of the file, so it
	   * must be wrong
	   */
	  curhdr->content->length = -1;
	}

	if (curhdr->content->length != -1)
	{
	  /* good content-length.  check to see if we know how many lines
	   * are in this message.
	   */
	  if (curhdr->lines == 0)
	  {
	    int cl = curhdr->content->length;

	    /* count the number of lines in this message */
	    if (fseeko (ctx->fp, loc, SEEK_SET) != 0)
	      dprint (1, (debugfile, "mbox_parse_mailbox: fseek() failed\n"));
	    while (cl-- > 0)
	    {
	      if (fgetc (ctx->fp) == '\n')
		curhdr->lines++;
	    }
	  }

	  /* return to the offset of the next message separator */
	  if (fseeko (ctx->fp, tmploc, SEEK_SET) != 0)
	    dprint (1, (debugfile, "mbox_parse_mailbox: fseek() failed\n"));
	}
      }

      ctx->msgcount++;

      if (!curhdr->env->return_path && return_path[0])
	curhdr->env->return_path = rfc822_parse_adrlist (curhdr->env->return_path, return_path);

      if (!curhdr->env->from)
	curhdr->env->from = rfc822_cpy_adr (curhdr->env->return_path, 0);

      lines = 0;
    }
    else
      lines++;
    
    loc = ftello (ctx->fp);
  }
  
  /*
   * Only set the content-length of the previous message if we have read more
   * than one message during _this_ invocation.  If this routine is called
   * when new mail is received, we need to make sure not to clobber what
   * previously was the last message since the headers may be sorted.
   */
  if (count > 0)
  {
    if (PREV->content->length < 0)
    {
      PREV->content->length = ftello (ctx->fp) - PREV->content->offset - 1;
      if (PREV->content->length < 0)
	PREV->content->length = 0;
    }

    if (!PREV->lines)
      PREV->lines = lines ? lines - 1 : 0;

    mx_update_context (ctx, count);
  }

  return (0);
}