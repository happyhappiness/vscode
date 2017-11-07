void mutt_parse_mime_message (CONTEXT *ctx, HEADER *cur)
{
  MESSAGE *msg;

  do {
    if (cur->content->type != TYPEMESSAGE &&
        cur->content->type != TYPEMULTIPART)
      break; /* nothing to do */

    if (cur->content->parts)
      break; /* The message was parsed earlier. */

    if ((msg = mx_open_message (ctx, cur->msgno)))
    {
      mutt_parse_part (msg->fp, cur->content);

      if (WithCrypto)
        cur->security = crypt_query (cur->content);

      mx_close_message (ctx, &msg);
    }
  } while (0);

  cur->attach_valid = 0;
}