static CURLcode smb_connection_state(struct connectdata *conn, bool *done)
{
  struct smb_conn *smbc = &conn->proto.smbc;
  struct smb_negotiate_response *nrsp;
  struct smb_header *h;
  CURLcode result;
  void *msg = NULL;

  if(smbc->state == SMB_CONNECTING) {
#ifdef USE_SSL
    if((conn->handler->flags & PROTOPT_SSL)) {
      bool ssl_done;
      result = Curl_ssl_connect_nonblocking(conn, FIRSTSOCKET, &ssl_done);
      if(result && result != CURLE_AGAIN)
        return result;
      if(!ssl_done)
        return CURLE_OK;
    }
#endif

    result = smb_send_negotiate(conn);
    if(result) {
      connclose(conn, "SMB: failed to send negotiate message");
      return result;
    }

    conn_state(conn, SMB_NEGOTIATE);
  }

  /* Send the previous message and check for a response */
  result = smb_send_and_recv(conn, &msg);
  if(result && result != CURLE_AGAIN) {
    connclose(conn, "SMB: failed to communicate");
    return result;
  }

  if(!msg)
    return CURLE_OK;

  h = msg;

  switch(smbc->state) {
  case SMB_NEGOTIATE:
    if(h->status || smbc->got < sizeof(*nrsp) + sizeof(smbc->challenge) - 1) {
      connclose(conn, "SMB: negotiation failed");
      return CURLE_COULDNT_CONNECT;
    }
    nrsp = msg;
    memcpy(smbc->challenge, nrsp->bytes, sizeof(smbc->challenge));
    smbc->session_key = smb_swap32(nrsp->session_key);
    result = smb_send_setup(conn);
    if(result) {
      connclose(conn, "SMB: failed to send setup message");
      return result;
    }
    conn_state(conn, SMB_SETUP);
    break;

  case SMB_SETUP:
    if(h->status) {
      connclose(conn, "SMB: authentication failed");
      return CURLE_LOGIN_DENIED;
    }
    smbc->uid = smb_swap16(h->uid);
    conn_state(conn, SMB_CONNECTED);
    *done = true;
    break;

  default:
    smb_pop_message(conn);
    return CURLE_OK; /* ignore */
  }

  smb_pop_message(conn);

  return CURLE_OK;
}