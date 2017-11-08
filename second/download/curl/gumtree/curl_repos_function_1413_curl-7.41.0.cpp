static CURLcode smb_send_open(struct connectdata *conn)
{
  struct smb_request *req = conn->data->req.protop;
  struct smb_nt_create msg;
  size_t byte_count;

  if((strlen(req->path) + 1) > sizeof(msg.bytes))
    return CURLE_FILESIZE_EXCEEDED;

  memset(&msg, 0, sizeof(msg));
  msg.word_count = SMB_WC_NT_CREATE_ANDX;
  msg.andx.command = SMB_COM_NO_ANDX_COMMAND;
  byte_count = strlen(req->path);
  msg.name_length = smb_swap16((unsigned short)byte_count);
  msg.share_access = smb_swap32(SMB_FILE_SHARE_ALL);
  if(conn->data->set.upload) {
    msg.access = smb_swap32(SMB_GENERIC_READ | SMB_GENERIC_WRITE);
    msg.create_disposition = smb_swap32(SMB_FILE_OVERWRITE_IF);
  }
  else {
    msg.access = smb_swap32(SMB_GENERIC_READ);
    msg.create_disposition = smb_swap32(SMB_FILE_OPEN);
  }
  msg.byte_count = smb_swap16((unsigned short) ++byte_count);
  strcpy(msg.bytes, req->path);

  return smb_send_message(conn, SMB_COM_NT_CREATE_ANDX, &msg,
                          sizeof(msg) - sizeof(msg.bytes) + byte_count);
}