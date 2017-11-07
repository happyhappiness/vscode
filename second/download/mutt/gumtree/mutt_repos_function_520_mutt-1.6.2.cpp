static int mbox_open_new_message (MESSAGE *msg, CONTEXT *dest, HEADER *hdr)
{
  msg->fp = dest->fp;
  return 0;
}