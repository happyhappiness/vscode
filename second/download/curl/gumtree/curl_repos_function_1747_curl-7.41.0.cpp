static CURLcode ftp_readresp(curl_socket_t sockfd,
                             struct pingpong *pp,
                             int *ftpcode, /* return the ftp-code if done */
                             size_t *size) /* size of the response */
{
  struct connectdata *conn = pp->conn;
  struct SessionHandle *data = conn->data;
#ifdef HAVE_GSSAPI
  char * const buf = data->state.buffer;
#endif
  CURLcode result = CURLE_OK;
  int code;

  result = Curl_pp_readresp(sockfd, pp, &code, size);

#if defined(HAVE_GSSAPI)
  /* handle the security-oriented responses 6xx ***/
  /* FIXME: some errorchecking perhaps... ***/
  switch(code) {
  case 631:
    code = Curl_sec_read_msg(conn, buf, PROT_SAFE);
    break;
  case 632:
    code = Curl_sec_read_msg(conn, buf, PROT_PRIVATE);
    break;
  case 633:
    code = Curl_sec_read_msg(conn, buf, PROT_CONFIDENTIAL);
    break;
  default:
    /* normal ftp stuff we pass through! */
    break;
  }
#endif

  /* store the latest code for later retrieval */
  data->info.httpcode=code;

  if(ftpcode)
    *ftpcode = code;

  if(421 == code) {
    /* 421 means "Service not available, closing control connection." and FTP
     * servers use it to signal that idle session timeout has been exceeded.
     * If we ignored the response, it could end up hanging in some cases.
     *
     * This response code can come at any point so having it treated
     * generically is a good idea.
     */
    infof(data, "We got a 421 - timeout!\n");
    state(conn, FTP_STOP);
    return CURLE_OPERATION_TIMEDOUT;
  }

  return result;
}