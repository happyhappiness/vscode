static void store_errmsg(const char *msg, int err)
{
  if (!err)
    sprintf(msgbuff, "%s", msg);
  else
    sprintf(msgbuff, "%s, errno %d, %s", msg, err, strerror(err));
}