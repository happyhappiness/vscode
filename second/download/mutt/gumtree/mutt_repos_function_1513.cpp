static int mh_open_new_message (MESSAGE * msg, CONTEXT * dest, HEADER * hdr)
{
  return mh_mkstemp (dest, &msg->fp, &msg->path);
}