static CURLcode ftp_state_type_resp(struct connectdata *conn,
                                    int ftpcode,
                                    ftpstate instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data=conn->data;

  if(ftpcode/100 != 2) {
    /* "sasserftpd" and "(u)r(x)bot ftpd" both responds with 226 after a
       successful 'TYPE I'. While that is not as RFC959 says, it is still a
       positive response code and we allow that. */
    failf(data, "Couldn't set desired mode");
    return CURLE_FTP_COULDNT_SET_TYPE;
  }
  if(ftpcode != 200)
    infof(data, "Got a %03d response code instead of the assumed 200\n",
          ftpcode);

  if(instate == FTP_TYPE)
    result = ftp_state_post_type(conn);
  else if(instate == FTP_LIST_TYPE)
    result = ftp_state_post_listtype(conn);
  else if(instate == FTP_RETR_TYPE)
    result = ftp_state_post_retrtype(conn);
  else if(instate == FTP_STOR_TYPE)
    result = ftp_state_post_stortype(conn);

  return result;
}