int mmdf_parse_mailbox (CONTEXT *ctx)
{
  char buf[HUGE_STRING];
  char return_path[LONG_STRING];
  int count = 0, oldmsgcount = ctx->msgcount;
  int lines;
  time_t t, tz;
  long loc, tmploc;
  HEADER *hdr;
  struct stat sb;
#ifdef NFS_ATTRIBUTE_HACK
  struct utimbuf newtime;
#endif

  if (stat (ctx->path, &sb) == -1)
  {
    mutt_perror (ctx->path);
    return (-1);
  }
  ctx->mtime = sb.st_mtime;
  ctx->size = sb.st_size;

#ifdef NFS_ATTRIBUTE_HACK
  if (sb.st_mtime > sb.st_atime)
  {
    newtime.modtime = sb.st_mtime;
    newtime.actime = time (NULL);
    utime (ctx->path, &newtime);
  }
#endif

  /* precompute the local timezone to speed up calculation of the
     received time */
  tz = mutt_local_tz (0);

  buf[sizeof (buf) - 1] = 0;
  
  FOREVER
  {
    if (fgets (buf, sizeof (buf) - 1, ctx->fp) == NULL)
      break;

    if (mutt_strcmp (buf, ctx->magic == M_MMDF ? MMDF_SEP : KENDRA_SEP) == 0)
    {
      loc = ftell (ctx->fp);
      
      count++;
      if (!ctx->quiet && ReadInc && ((count % ReadInc == 0) || count == 1))
	mutt_message (_("Reading %s... %d (%d%%)"), ctx->path, count,
		      loc / (ctx->size / 100 + 1));


      if (ctx->msgcount == ctx->hdrmax)
	mx_alloc_memory (ctx);
      ctx->hdrs[ctx->msgcount] = hdr = mutt_new_header ();
      hdr->offset = loc;
      hdr->index = ctx->msgcount;

      if (fgets (buf, sizeof (buf) - 1, ctx->fp) == NULL)
      {
	/* TODO: memory leak??? */
	dprint (1, (debugfile, "mmdf_parse_mailbox: unexpected EOF\n"));
	break;
      }

      return_path[0] = 0;

      if (!is_from (buf, return_path, sizeof (return_path), &t))
      {
	if (fseek (ctx->fp, loc, SEEK_SET) != 0)
	{
	  dprint (1, (debugfile, "mmdf_parse_mailbox: fseek() failed\n"));
	  mutt_error _("Mailbox is corrupt!");
	  return (-1);
	}
      } 
      else
	hdr->received = t - tz;

      hdr->env = mutt_read_rfc822_header (ctx->fp, hdr, 0, 0);

      loc = ftell (ctx->fp);

      if (hdr->content->length > 0 && hdr->lines > 0)
      {
	tmploc = loc + hdr->content->length;

	if (0 < tmploc && tmploc < ctx->size)
	{
	  if (fseek (ctx->fp, tmploc, SEEK_SET) != 0 ||
	      fgets (buf, sizeof (buf) - 1, ctx->fp) == NULL ||
	      mutt_strcmp (ctx->magic == M_MMDF ? MMDF_SEP : KENDRA_SEP, buf) != 0)
	  {
	    if (fseek (ctx->fp, loc, SEEK_SET) != 0)
	      dprint (1, (debugfile, "mmdf_parse_mailbox: fseek() failed\n"));
	    hdr->content->length = -1;
	  }
	}
	else
	  hdr->content->length = -1;
      }
      else
	hdr->content->length = -1;

      if (hdr->content->length < 0)
      {
	lines = -1;
	do {
	  loc = ftell (ctx->fp);
	  if (fgets (buf, sizeof (buf) - 1, ctx->fp) == NULL)
	    break;
	  lines++;
	} while (mutt_strcmp (buf, ctx->magic == M_MMDF ? MMDF_SEP : KENDRA_SEP) != 0);

	hdr->lines = lines;
	hdr->content->length = loc - hdr->content->offset;
      }

      if (!hdr->env->return_path && return_path[0])
	hdr->env->return_path = rfc822_parse_adrlist (hdr->env->return_path, return_path);

      if (!hdr->env->from)
	hdr->env->from = rfc822_cpy_adr (hdr->env->return_path);

      ctx->msgcount++;
      if(ctx->magic == M_KENDRA && feof(ctx->fp))
	break;
    }
    else
    {
      dprint (1, (debugfile, "mmdf_parse_mailbox: corrupt mailbox!\n"));
      mutt_error _("Mailbox is corrupt!");
      return (-1);
    }
  }

  if (ctx->msgcount > oldmsgcount)
    mx_update_context (ctx, ctx->msgcount - oldmsgcount);

  return (0);
}