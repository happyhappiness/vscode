int _mutt_save_message (HEADER *h, CONTEXT *ctx, int delete, int decode, int decrypt)
{
  int cmflags, chflags;
  int rc;
  
  set_copy_flags (h, decode, decrypt, &cmflags, &chflags);

  if (decode || decrypt)
    mutt_parse_mime_message (Context, h);

  if ((rc = mutt_append_message (ctx, Context, h, cmflags, chflags)) != 0)
    return rc;

  if (delete)
  {
    mutt_set_flag (Context, h, MUTT_DELETE, 1);
    mutt_set_flag (Context, h, MUTT_PURGE, 1);
    if (option (OPTDELETEUNTAG))
      mutt_set_flag (Context, h, MUTT_TAG, 0);
  }
  
  return 0;
}