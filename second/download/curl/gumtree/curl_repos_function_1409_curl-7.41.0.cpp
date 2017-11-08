static CURLcode smb_send_message(struct connectdata *conn, unsigned char cmd,
                                 const void *msg, size_t msg_len)
{
  smb_format_message(conn, (struct smb_header *)conn->data->state.uploadbuffer,
                     cmd, msg_len);
  memcpy(conn->data->state.uploadbuffer + sizeof(struct smb_header),
         msg, msg_len);

  return smb_send(conn, sizeof(struct smb_header) + msg_len, 0);
}