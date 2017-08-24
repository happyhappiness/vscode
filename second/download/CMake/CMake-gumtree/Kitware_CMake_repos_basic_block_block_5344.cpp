{
  struct smb_request *req = conn->data->req.protop;
  struct smb_tree_connect msg;
  char *p = msg.bytes;

  size_t byte_count = strlen(conn->host.name) + strlen(req->share);
  byte_count += strlen(SERVICENAME) + 5; /* 2 nulls and 3 backslashes */
  if(byte_count > sizeof(msg.bytes))
    return CURLE_FILESIZE_EXCEEDED;

  memset(&msg, 0, sizeof(msg));
  msg.word_count = SMB_WC_TREE_CONNECT_ANDX;
  msg.andx.command = SMB_COM_NO_ANDX_COMMAND;
  msg.pw_len = 0;
  MSGCAT("\\\\");
  MSGCAT(conn->host.name);
  MSGCAT("\\");
  MSGCATNULL(req->share);
  MSGCATNULL(SERVICENAME); /* Match any type of service */
  byte_count = p - msg.bytes;
  msg.byte_count = smb_swap16((unsigned short)byte_count);

  return smb_send_message(conn, SMB_COM_TREE_CONNECT_ANDX, &msg,
                          sizeof(msg) - sizeof(msg.bytes) + byte_count);
}