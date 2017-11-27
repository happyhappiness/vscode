static int ipc_read_msg(void) /* {{{ */
{
  struct msginfo msginfo;

  if (msgctl(0, MSG_INFO, (struct msqid_ds *)(void *)&msginfo) < 0) {
    ERROR("Kernel is not configured for message queues");
    return (-1);
  }
  ipc_submit_g("msg", "count", "queues", msginfo.msgmni);
  ipc_submit_g("msg", "count", "headers", msginfo.msgmap);
  ipc_submit_g("msg", "count", "space", msginfo.msgtql);

  return (0);
}