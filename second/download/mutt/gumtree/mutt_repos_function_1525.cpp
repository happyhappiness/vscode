static int mh_rewrite_message (CONTEXT * ctx, int msgno)
{
  HEADER *h = ctx->hdrs[msgno];
  MESSAGE *dest;

  int rc;
  short restore = 1;
  char oldpath[_POSIX_PATH_MAX];
  char newpath[_POSIX_PATH_MAX];
  char partpath[_POSIX_PATH_MAX];

  long old_body_offset = h->content->offset;
  long old_body_length = h->content->length;
  long old_hdr_lines = h->lines;

  if ((dest = mx_open_new_message (ctx, h, 0)) == NULL)
    return -1;

  if ((rc = mutt_copy_message (dest->fp, ctx, h,
			       MUTT_CM_UPDATE, CH_UPDATE | CH_UPDATE_LEN)) == 0)
  {
    snprintf (oldpath, _POSIX_PATH_MAX, "%s/%s", ctx->path, h->path);
    strfcpy (partpath, h->path, _POSIX_PATH_MAX);

    if (ctx->magic == MUTT_MAILDIR)
      rc = _maildir_commit_message (ctx, dest, h);
    else
      rc = _mh_commit_message (ctx, dest, h, 0);

    mx_close_message (ctx, &dest);

    if (rc == 0)
    {
      unlink (oldpath);
      restore = 0;
    }

    /* 
     * Try to move the new message to the old place.
     * (MH only.)
     *
     * This is important when we are just updating flags.
     *
     * Note that there is a race condition against programs which
     * use the first free slot instead of the maximum message
     * number.  Mutt does _not_ behave like this.
     * 
     * Anyway, if this fails, the message is in the folder, so
     * all what happens is that a concurrently running mutt will
     * lose flag modifications.
     */

    if (ctx->magic == MUTT_MH && rc == 0)
    {
      snprintf (newpath, _POSIX_PATH_MAX, "%s/%s", ctx->path, h->path);
      if ((rc = safe_rename (newpath, oldpath)) == 0)
	mutt_str_replace (&h->path, partpath);
    }
  }
  else
    mx_close_message (ctx, &dest);

  if (rc == -1 && restore)
  {
    h->content->offset = old_body_offset;
    h->content->length = old_body_length;
    h->lines = old_hdr_lines;
  }

  mutt_free_body (&h->content->parts);
  return rc;
}