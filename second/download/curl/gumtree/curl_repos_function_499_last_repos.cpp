static void store_errmsg(const char *msg, int err)
{
  if(!err)
    snprintf(msgbuff, sizeof(msgbuff), "%s", msg);
  else
    snprintf(msgbuff, sizeof(msgbuff), "%s, errno %d, %s", msg, err,
             strerror(err));
}