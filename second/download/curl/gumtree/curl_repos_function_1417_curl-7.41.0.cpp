static CURLcode smb_send_write(struct connectdata *conn)
{
  struct smb_write *msg = (struct smb_write *)conn->data->state.uploadbuffer;
  struct smb_request *req = conn->data->req.protop;
  curl_off_t offset = conn->data->req.offset;

  curl_off_t upload_size = conn->data->req.size - conn->data->req.bytecount;
  if(upload_size >= MAX_PAYLOAD_SIZE - 1) /* There is one byte of padding */
    upload_size = MAX_PAYLOAD_SIZE - 1;

  memset(msg, 0, sizeof(*msg));
  msg->word_count = SMB_WC_WRITE_ANDX;
  msg->andx.command = SMB_COM_NO_ANDX_COMMAND;
  msg->fid = smb_swap16(req->fid);
  msg->offset = smb_swap32((unsigned int) offset);
  msg->offset_high = smb_swap32((unsigned int) (offset >> 32));
  msg->data_length = smb_swap16((unsigned short) upload_size);
  msg->data_offset = smb_swap16(sizeof(*msg) - sizeof(unsigned int));
  msg->byte_count = smb_swap16((unsigned short) (upload_size + 1));

  smb_format_message(conn, &msg->h, SMB_COM_WRITE_ANDX,
                     sizeof(*msg) - sizeof(msg->h) + (size_t) upload_size);

  return smb_send(conn, sizeof(*msg), (size_t) upload_size);
}