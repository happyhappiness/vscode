static CURLcode ftp_state_size_resp(struct connectdata *conn,
                                    int ftpcode,
                                    ftpstate instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data=conn->data;
  curl_off_t filesize;
  char *buf = data->state.buffer;

  /* get the size from the ascii string: */
  filesize = (ftpcode == 213)?curlx_strtoofft(buf+4, NULL, 0):-1;

  if(instate == FTP_SIZE) {
    if(-1 != filesize) {
      snprintf(buf, sizeof(data->state.buffer),
               "Content-Length: %" FORMAT_OFF_T "\r\n", filesize);
      result = Curl_client_write(data, CLIENTWRITE_BOTH, buf, 0);
      if(result)
        return result;
    }
    result = ftp_state_post_size(conn);
  }
  else if(instate == FTP_RETR_SIZE)
    result = ftp_state_post_retr_size(conn, filesize);
  else if(instate == FTP_STOR_SIZE) {
    conn->resume_from = filesize;
    result = ftp_state_ul_setup(conn, TRUE);
  }

  return result;
}