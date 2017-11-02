static CURLcode smb_send_close(struct connectdata *conn)
{
  struct smb_request *req = conn->data->req.protop;
  struct smb_close msg;

  memset(&msg, 0, sizeof(msg));
  msg.word_count = SMB_WC_CLOSE;
  msg.fid = smb_swap16(req->fid);

  return smb_send_message(conn, SMB_COM_CLOSE, &msg, sizeof(msg));
}