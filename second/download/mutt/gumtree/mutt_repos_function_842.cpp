int
mutt_copy_message (FILE *fpout, CONTEXT *src, HEADER *hdr, int flags,
		   int chflags)
{
  MESSAGE *msg;
  int r;
  
  if ((msg = mx_open_message (src, hdr->msgno)) == NULL)
    return -1;
  if ((r = _mutt_copy_message (fpout, msg->fp, hdr, hdr->content, flags, chflags)) == 0 
      && (ferror (fpout) || feof (fpout)))
  {
    dprint (1, (debugfile, "_mutt_copy_message failed to detect EOF!\n"));
    r = -1;
  }
  mx_close_message (src, &msg);
  return r;
}