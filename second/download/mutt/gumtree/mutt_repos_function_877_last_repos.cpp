int
_mutt_append_message (CONTEXT *dest, FILE *fpin, CONTEXT *src, HEADER *hdr,
		      BODY *body, int flags, int chflags)
{
  char buf[STRING];
  MESSAGE *msg;
  int r;

  fseeko (fpin, hdr->offset, 0);
  if (fgets (buf, sizeof (buf), fpin) == NULL)
    return -1;
  
  if ((msg = mx_open_new_message (dest, hdr, is_from (buf, NULL, 0, NULL) ? 0 : MUTT_ADD_FROM)) == NULL)
    return -1;
  if (dest->magic == MUTT_MBOX || dest->magic == MUTT_MMDF)
    chflags |= CH_FROM | CH_FORCE_FROM;
  chflags |= (dest->magic == MUTT_MAILDIR ? CH_NOSTATUS : CH_UPDATE);
  r = _mutt_copy_message (msg->fp, fpin, hdr, body, flags, chflags);
  if (mx_commit_message (msg, dest) != 0)
    r = -1;

  mx_close_message (dest, &msg);
  return r;
}