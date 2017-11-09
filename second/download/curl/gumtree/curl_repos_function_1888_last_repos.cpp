static CURLcode InitiateTransfer(struct connectdata *conn)
{
  struct Curl_easy *data = conn->data;
  struct FTP *ftp = data->req.protop;
  CURLcode result = CURLE_OK;

  if(conn->bits.ftp_use_data_ssl) {
    /* since we only have a plaintext TCP connection here, we must now
     * do the TLS stuff */
    infof(data, "Doing the SSL/TLS handshake on the data stream\n");
    result = Curl_ssl_connect(conn, SECONDARYSOCKET);
    if(result)
      return result;
  }

  if(conn->proto.ftpc.state_saved == FTP_STOR) {
    *(ftp->bytecountp) = 0;

    /* When we know we're uploading a specified file, we can get the file
       size prior to the actual upload. */

    Curl_pgrsSetUploadSize(data, data->state.infilesize);

    /* set the SO_SNDBUF for the secondary socket for those who need it */
    Curl_sndbufset(conn->sock[SECONDARYSOCKET]);

    Curl_setup_transfer(conn, -1, -1, FALSE, NULL, /* no download */
                        SECONDARYSOCKET, ftp->bytecountp);
  }
  else {
    /* FTP download: */
    Curl_setup_transfer(conn, SECONDARYSOCKET,
                        conn->proto.ftpc.retr_size_saved, FALSE,
                        ftp->bytecountp, -1, NULL); /* no upload here */
  }

  conn->proto.ftpc.pp.pending_resp = TRUE; /* expect server response */
  state(conn, FTP_STOP);

  return CURLE_OK;
}