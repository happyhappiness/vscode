static int edit_one_message (CONTEXT *ctx, HEADER *cur)
{
  char tmp[_POSIX_PATH_MAX];
  char buff[STRING];
  int omagic;
  int oerrno;
  int rc;

  unsigned short o_read;
  unsigned short o_old;

  int of, cf;
  
  CONTEXT tmpctx;
  MESSAGE *msg;

  FILE *fp = NULL;

  struct stat sb;
  time_t mtime = 0;
  
  mutt_mktemp (tmp, sizeof (tmp));

  omagic = DefaultMagic;
  DefaultMagic = MUTT_MBOX;

  rc = (mx_open_mailbox (tmp, MUTT_NEWFOLDER, &tmpctx) == NULL) ? -1 : 0;

  DefaultMagic = omagic;

  if (rc == -1)
  {
    mutt_error (_("could not create temporary folder: %s"), strerror (errno));
    return -1;
  }

  rc = mutt_append_message (&tmpctx, ctx, cur, 0, CH_NOLEN |
	((ctx->magic == MUTT_MBOX || ctx->magic == MUTT_MMDF) ? 0 : CH_NOSTATUS));
  oerrno = errno;

  mx_close_mailbox (&tmpctx, NULL);

  if (rc == -1)
  {
    mutt_error (_("could not write temporary mail folder: %s"), strerror (oerrno));
    goto bail;
  }

  if ((rc = stat (tmp, &sb)) == -1)
  {
    mutt_error (_("Can't stat %s: %s"), tmp, strerror (errno));
    goto bail;
  }

  /*
   * 2002-09-05 me@sigpipe.org
   * The file the user is going to edit is not a real mbox, so we need to
   * truncate the last newline in the temp file, which is logically part of
   * the message separator, and not the body of the message.  If we fail to
   * remove it, the message will grow by one line each time the user edits
   * the message.
   */
  if (sb.st_size != 0 && truncate (tmp, sb.st_size - 1) == -1)
  {
    mutt_error (_("could not truncate temporary mail folder: %s"),
		strerror (errno));
    goto bail;
  }

  mtime = mutt_decrease_mtime (tmp, &sb);

  mutt_edit_file (NONULL(Editor), tmp);

  if ((rc = stat (tmp, &sb)) == -1)
  {
    mutt_error (_("Can't stat %s: %s"), tmp, strerror (errno));
    goto bail;
  }
  
  if (sb.st_size == 0)
  {
    mutt_message (_("Message file is empty!"));
    rc = 1;
    goto bail;
  }

  if (sb.st_mtime == mtime)
  {
    mutt_message (_("Message not modified!"));
    rc = 1;
    goto bail;
  }

  if ((fp = fopen (tmp, "r")) == NULL)
  {
    rc = -1;
    mutt_error (_("Can't open message file: %s"), strerror (errno));
    goto bail;
  }

  if (mx_open_mailbox (ctx->path, MUTT_APPEND, &tmpctx) == NULL)
  {
    rc = -1;
    /* L10N: %s is from strerror(errno) */
    mutt_error (_("Can't append to folder: %s"), strerror (errno));
    goto bail;
  }

  of = 0;
  cf = ((tmpctx.magic == MUTT_MBOX || tmpctx.magic == MUTT_MMDF) ? 0 : CH_NOSTATUS);
  
  if (fgets (buff, sizeof (buff), fp) && is_from (buff, NULL, 0, NULL))
  {
    if (tmpctx.magic == MUTT_MBOX || tmpctx.magic == MUTT_MMDF)
      cf = CH_FROM | CH_FORCE_FROM;
  }
  else
    of = MUTT_ADD_FROM;

  /* 
   * XXX - we have to play games with the message flags to avoid
   * problematic behavior with maildir folders.
   *
   */

  o_read = cur->read; o_old = cur->old;
  cur->read = cur->old = 0;
  msg = mx_open_new_message (&tmpctx, cur, of);
  cur->read = o_read; cur->old = o_old;

  if (msg == NULL)
  {
    mutt_error (_("Can't append to folder: %s"), strerror (errno));
    mx_close_mailbox (&tmpctx, NULL);
    goto bail;
  }

  if ((rc = mutt_copy_hdr (fp, msg->fp, 0, sb.st_size, CH_NOLEN | cf, NULL)) == 0)
  {
    fputc ('\n', msg->fp);
    rc = mutt_copy_stream (fp, msg->fp);
  }

  rc = mx_commit_message (msg, &tmpctx);
  mx_close_message (&tmpctx, &msg);
  
  mx_close_mailbox (&tmpctx, NULL);
  
  bail:
  if (fp) safe_fclose (&fp);

  if (rc >= 0)
    unlink (tmp);

  if (rc == 0)
  {
    mutt_set_flag (Context, cur, MUTT_DELETE, 1);
    mutt_set_flag (Context, cur, MUTT_PURGE, 1);
    mutt_set_flag (Context, cur, MUTT_READ, 1);

    if (option (OPTDELETEUNTAG))
      mutt_set_flag (Context, cur, MUTT_TAG, 0);
  }
  else if (rc == -1)
    mutt_message (_("Error. Preserving temporary file: %s"), tmp);

    
  return rc;
}