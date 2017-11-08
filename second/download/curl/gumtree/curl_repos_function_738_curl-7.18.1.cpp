static CURLcode tftp_connect(struct connectdata *conn, bool *done)
{
  CURLcode code;
  tftp_state_data_t *state;
  int rc;

  /* If there already is a protocol-specific struct allocated for this
     sessionhandle, deal with it */
  Curl_reset_reqproto(conn);

  state = conn->data->state.proto.tftp;
  if(!state) {
    state = conn->data->state.proto.tftp = calloc(sizeof(tftp_state_data_t),
                                                  1);
    if(!state)
      return CURLE_OUT_OF_MEMORY;
  }

  conn->bits.close = FALSE; /* keep it open if possible */

  state->conn = conn;
  state->sockfd = state->conn->sock[FIRSTSOCKET];
  state->state = TFTP_STATE_START;
  state->error = TFTP_ERR_NONE;

  ((struct sockaddr *)&state->local_addr)->sa_family =
    (unsigned short)(conn->ip_addr->ai_family);

  tftp_set_timeouts(state);

  if(!conn->bits.bound) {
    /* If not already bound, bind to any interface, random UDP port. If it is
     * reused or a custom local port was desired, this has already been done!
     *
     * We once used the size of the local_addr struct as the third argument for
     * bind() to better work with IPv6 or whatever size the struct could have,
     * but we learned that at least Tru64, AIX and IRIX *requires* the size of
     * that argument to match the exact size of a 'sockaddr_in' struct when
     * running IPv4-only.
     *
     * Therefore we use the size from the address we connected to, which we
     * assume uses the same IP version and thus hopefully this works for both
     * IPv4 and IPv6...
     */
    rc = bind(state->sockfd, (struct sockaddr *)&state->local_addr,
              conn->ip_addr->ai_addrlen);
    if(rc) {
      failf(conn->data, "bind() failed; %s",
            Curl_strerror(conn, SOCKERRNO));
      return CURLE_COULDNT_CONNECT;
    }
    conn->bits.bound = TRUE;
  }

  Curl_pgrsStartNow(conn->data);

  *done = TRUE;
  code = CURLE_OK;
  return(code);
}