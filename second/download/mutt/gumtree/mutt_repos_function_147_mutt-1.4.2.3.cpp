void _mutt_save_message (HEADER *h, CONTEXT *ctx, int delete, int decode, int decrypt)
{
  int cmflags, chflags;
  
  set_copy_flags (h, decode, decrypt, &cmflags, &chflags);

  if (decode || decrypt)
    mutt_parse_mime_message (Context, h);

  if (mutt_append_message (ctx, Context, h, cmflags, chflags) == 0 && delete)
  {
    mutt_set_flag (Context, h, M_DELETE, 1);
    if (option (OPTDELETEUNTAG))
      mutt_set_flag (Context, h, M_TAG, 0);
  }
}