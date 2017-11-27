static int ipc_read_msg (void) /* {{{ */
{
  ipcinfo_msg_t *ipcinfo_msg;
  uint32_t msg_used_space=0;
  uint32_t msg_alloc_queues=0;
  msgqnum32_t msg_qnum=0;
  int n;

  ipcinfo_msg = (ipcinfo_msg_t *)ipc_get_info(0,
    GET_IPCINFO_MSG_ALL, IPCINFO_MSG_VERSION, sizeof(ipcinfo_msg_t), &n);
  if (ipcinfo_msg == NULL)
    return -1;

  for (int i=0; i<n; i++) {
    msg_alloc_queues++;
    msg_used_space += ipcinfo_msg[i].msg_cbytes;
    msg_qnum += ipcinfo_msg[i].msg_qnum;
  }
  free(ipcinfo_msg);

  ipc_submit_g("msg", "count", "queues", msg_alloc_queues);
  ipc_submit_g("msg", "count", "headers", msg_qnum);
  ipc_submit_g("msg", "count", "space", msg_used_space);

  return (0);
}