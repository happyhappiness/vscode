void mutt_parse_mime_message (CONTEXT *ctx, HEADER *cur)
{
  MESSAGE *msg;

  if (cur->content->type != TYPEMESSAGE && cur->content->type != TYPEMULTIPART)
    return; /* nothing to do */

  if (cur->content->parts)
    return; /* The message was parsed earlier. */

  if ((msg = mx_open_message (ctx, cur->msgno)))
  {
    mutt_parse_part (msg->fp, cur->content);


#ifdef HAVE_PGP
    cur->pgp = pgp_query (cur->content);
#endif /* HAVE_PGP */


    mx_close_message (&msg);
  }
}