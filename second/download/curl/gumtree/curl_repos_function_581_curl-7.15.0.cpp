static CURLcode ftp_state_user_resp(struct connectdata *conn,
                                    int ftpcode,
                                    ftpstate instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  struct FTP *ftp = conn->proto.ftp;
  (void)instate; /* no use for this yet */

  if((ftpcode == 331) && (ftp->state == FTP_USER)) {
    /* 331 Password required for ...
       (the server requires to send the user's password too) */
    NBFTPSENDF(conn, "PASS %s", ftp->passwd?ftp->passwd:"");
    state(conn, FTP_PASS);
  }
  else if(ftpcode/100 == 2) {
    /* 230 User ... logged in.
       (the user logged in with or without password) */
    result = ftp_state_loggedin(conn);
  }
  else if(ftpcode == 332) {
    if(data->set.ftp_account) {
      NBFTPSENDF(conn, "ACCT %s", data->set.ftp_account);
      state(conn, FTP_ACCT);
    }
    else {
      failf(data, "ACCT requested but none available");
      result = CURLE_LOGIN_DENIED;
    }
  }
  else {
    /* All other response codes, like:

    530 User ... access denied
    (the server denies to log the specified user) */
    failf(data, "Access denied: %03d", ftpcode);
    result = CURLE_LOGIN_DENIED;
  }
  return result;
}