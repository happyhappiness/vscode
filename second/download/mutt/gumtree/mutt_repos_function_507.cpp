BODY *mutt_parse_messageRFC822 (FILE *fp, BODY *parent)
{
  BODY *msg;

  parent->hdr = mutt_new_header ();
  parent->hdr->offset = ftello (fp);
  parent->hdr->env = mutt_read_rfc822_header (fp, parent->hdr, 0, 0);
  msg = parent->hdr->content;

  /* ignore the length given in the content-length since it could be wrong
     and we already have the info to calculate the correct length */
  /* if (msg->length == -1) */
  msg->length = parent->length - (msg->offset - parent->offset);

  /* if body of this message is empty, we can end up with a negative length */
  if (msg->length < 0)
    msg->length = 0;

  mutt_parse_part(fp, msg);
  return (msg);
}