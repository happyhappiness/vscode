static CURLcode smb_send_tree_disconnect(struct connectdata *conn)
{
  struct smb_tree_disconnect msg;

  memset(&msg, 0, sizeof(msg));

  return smb_send_message(conn, SMB_COM_TREE_DISCONNECT, &msg, sizeof(msg));
}