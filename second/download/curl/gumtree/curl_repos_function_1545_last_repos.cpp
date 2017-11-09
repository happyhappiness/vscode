static CURLcode smb_flush(struct connectdata *conn)
{
  struct smb_conn *smbc = &conn->proto.smbc;
  ssize_t bytes_written;
  ssize_t len = smbc->send_size - smbc->sent;
  CURLcode result;

  if(!smbc->send_size)
    return CURLE_OK;

  result = Curl_write(conn, FIRSTSOCKET,
                      conn->data->state.uploadbuffer + smbc->sent,
                      len, &bytes_written);
  if(result)
    return result;

  if(bytes_written != len)
    smbc->sent += bytes_written;
  else
    smbc->send_size = 0;

  return CURLE_OK;
}