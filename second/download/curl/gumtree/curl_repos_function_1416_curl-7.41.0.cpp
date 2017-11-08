static CURLcode smb_send_read(struct connectdata *conn)
{
  struct smb_request *req = conn->data->req.protop;
  curl_off_t offset = conn->data->req.offset;
  struct smb_read msg;

  memset(&msg, 0, sizeof(msg));
  msg.word_count = SMB_WC_READ_ANDX;
  msg.andx.command = SMB_COM_NO_ANDX_COMMAND;
  msg.fid = smb_swap16(req->fid);
  msg.offset = smb_swap32((unsigned int) offset);
  msg.offset_high = smb_swap32((unsigned int) (offset >> 32));
  msg.min_bytes = smb_swap16(MAX_PAYLOAD_SIZE);
  msg.max_bytes = smb_swap16(MAX_PAYLOAD_SIZE);

  return smb_send_message(conn, SMB_COM_READ_ANDX, &msg, sizeof(msg));
}