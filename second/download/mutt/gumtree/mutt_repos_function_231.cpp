static int _mutt_check_traditional_pgp (HEADER *h, int *redraw)
{
  MESSAGE *msg;
  int rv = 0;
  
  h->security |= PGP_TRADITIONAL_CHECKED;
  
  mutt_parse_mime_message (Context, h);
  if ((msg = mx_open_message (Context, h->msgno)) == NULL)
    return 0;
  if (crypt_pgp_check_traditional (msg->fp, h->content, 0))
  {
    h->security = crypt_query (h->content);
    *redraw |= REDRAW_FULL;
    rv = 1;
  }
  
  h->security |= PGP_TRADITIONAL_CHECKED;
  mx_close_message (Context, &msg);
  return rv;
}