static CURLcode ftp_state_stor_resp(struct connectdata *conn,
                                    int ftpcode)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  struct FTP *ftp = conn->proto.ftp;

  if(ftpcode>=400) {
    failf(data, "Failed FTP upload: %0d", ftpcode);
    /* oops, we never close the sockets! */
    return CURLE_FTP_COULDNT_STOR_FILE;
  }

  if(data->set.ftp_use_port) {
    /* BLOCKING */
    /* PORT means we are now awaiting the server to connect to us. */
    result = AllowServerConnect(conn);
    if( result )
      return result;
  }

  if(conn->ssl[SECONDARYSOCKET].use) {
    /* since we only have a plaintext TCP connection here, we must now
       do the TLS stuff */
    infof(data, "Doing the SSL/TLS handshake on the data stream\n");
    /* BLOCKING */
    result = Curl_ssl_connect(conn, SECONDARYSOCKET);
    if(result)
      return result;
  }

  *(ftp->bytecountp)=0;

  /* When we know we're uploading a specified file, we can get the file
     size prior to the actual upload. */

  Curl_pgrsSetUploadSize(data, data->set.infilesize);

  result = Curl_Transfer(conn, -1, -1, FALSE, NULL, /* no download */
                         SECONDARYSOCKET, ftp->bytecountp);
  state(conn, FTP_STOP);

  return result;
}