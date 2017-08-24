{
  struct smb_conn *smbc = &conn->proto.smbc;

  if(!numsocks)
    return GETSOCK_BLANK;

  socks[0] = conn->sock[FIRSTSOCKET];

  if(smbc->send_size || smbc->upload_size)
    return GETSOCK_WRITESOCK(0);

  return GETSOCK_READSOCK(0);
}