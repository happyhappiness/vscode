int
mutt_append_message (CONTEXT *dest, CONTEXT *src, HEADER *hdr, int cmflags,
		     int chflags)
{
  MESSAGE *msg;
  int r;

  if ((msg = mx_open_message (src, hdr->msgno)) == NULL)
    return -1;
  r = _mutt_append_message (dest, msg->fp, src, hdr, hdr->content, cmflags, chflags);
  mx_close_message (src, &msg);
  return r;
}