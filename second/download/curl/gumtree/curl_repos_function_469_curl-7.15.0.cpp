CURLcode Curl_tftp_connect(struct connectdata *conn, bool *done)
{
  CURLcode code;
  tftp_state_data_t     *state;
  int rc;

  if((state = conn->proto.tftp = calloc(sizeof(tftp_state_data_t), 1))==NULL) {
    return CURLE_OUT_OF_MEMORY;
  }

  state->conn = conn;
  state->sockfd = state->conn->sock[FIRSTSOCKET];
  state->state = TFTP_STATE_START;

#ifdef WIN32
  /* AF_UNSPEC == 0 (from above calloc) doesn't work on Winsock */
  state->local_addr.sa_family = conn->ip_addr->ai_family;
#endif

  tftp_set_timeouts(state);

  /* Bind to any interface, random UDP port */
  rc = bind(state->sockfd, &state->local_addr, sizeof(state->local_addr));
  if(rc) {
    failf(conn->data, "bind() failed; %s\n",
          Curl_strerror(conn,Curl_ourerrno()));
    return CURLE_COULDNT_CONNECT;
  }

  Curl_pgrsStartNow(conn->data);

  *done = TRUE;
  code = CURLE_OK;
  return(code);
}