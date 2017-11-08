static CURLcode smb_send_and_recv(struct connectdata *conn, void **msg)
{
  struct smb_conn *smbc = &conn->proto.smbc;
  CURLcode result;

  /* Check if there is data in the transfer buffer */
  if(!smbc->send_size && smbc->upload_size) {
    int nread = smbc->upload_size > UPLOAD_BUFSIZE ? UPLOAD_BUFSIZE :
      (int) smbc->upload_size;
    conn->data->req.upload_fromhere = conn->data->state.uploadbuffer;
    result = Curl_fillreadbuffer(conn, nread, &nread);
    if(result && result != CURLE_AGAIN)
      return result;
    if(!nread)
      return CURLE_OK;

    smbc->upload_size -= nread;
    smbc->send_size = nread;
    smbc->sent = 0;
  }

  /* Check if there is data to send */
  if(smbc->send_size) {
    result = smb_flush(conn);
    if(result)
      return result;
  }

  /* Check if there is still data to be sent */
  if(smbc->send_size || smbc->upload_size)
    return CURLE_AGAIN;

  return smb_recv_message(conn, msg);
}