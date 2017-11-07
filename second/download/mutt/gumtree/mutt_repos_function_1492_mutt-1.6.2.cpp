int mh_commit_message (CONTEXT * ctx, MESSAGE * msg, HEADER * hdr)
{
  return _mh_commit_message (ctx, msg, hdr, 1);
}