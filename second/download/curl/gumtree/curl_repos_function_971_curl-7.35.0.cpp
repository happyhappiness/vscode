static CURLcode imap_statemach_act(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  curl_socket_t sock = conn->sock[FIRSTSOCKET];
  int imapcode;
  struct imap_conn *imapc = &conn->proto.imapc;
  struct pingpong *pp = &imapc->pp;
  size_t nread = 0;

  /* Busy upgrading the connection; right now all I/O is SSL/TLS, not IMAP */
  if(imapc->state == IMAP_UPGRADETLS)
    return imap_perform_upgrade_tls(conn);

  /* Flush any data that needs to be sent */
  if(pp->sendleft)
    return Curl_pp_flushsend(pp);

  do {
    /* Read the response from the server */
    result = Curl_pp_readresp(sock, pp, &imapcode, &nread);
    if(result)
      return result;

    /* Was there an error parsing the response line? */
    if(imapcode == -1)
      return CURLE_FTP_WEIRD_SERVER_REPLY;

    if(!imapcode)
      break;

    /* We have now received a full IMAP server response */
    switch(imapc->state) {
    case IMAP_SERVERGREET:
      result = imap_state_servergreet_resp(conn, imapcode, imapc->state);
      break;

    case IMAP_CAPABILITY:
      result = imap_state_capability_resp(conn, imapcode, imapc->state);
      break;

    case IMAP_STARTTLS:
      result = imap_state_starttls_resp(conn, imapcode, imapc->state);
      break;

    case IMAP_AUTHENTICATE_PLAIN:
      result = imap_state_auth_plain_resp(conn, imapcode, imapc->state);
      break;

    case IMAP_AUTHENTICATE_LOGIN:
      result = imap_state_auth_login_resp(conn, imapcode, imapc->state);
      break;

    case IMAP_AUTHENTICATE_LOGIN_PASSWD:
      result = imap_state_auth_login_password_resp(conn, imapcode,
                                                   imapc->state);
      break;

#ifndef CURL_DISABLE_CRYPTO_AUTH
    case IMAP_AUTHENTICATE_CRAMMD5:
      result = imap_state_auth_cram_resp(conn, imapcode, imapc->state);
      break;

    case IMAP_AUTHENTICATE_DIGESTMD5:
      result = imap_state_auth_digest_resp(conn, imapcode, imapc->state);
      break;

    case IMAP_AUTHENTICATE_DIGESTMD5_RESP:
      result = imap_state_auth_digest_resp_resp(conn, imapcode, imapc->state);
      break;
#endif

#ifdef USE_NTLM
    case IMAP_AUTHENTICATE_NTLM:
      result = imap_state_auth_ntlm_resp(conn, imapcode, imapc->state);
      break;

    case IMAP_AUTHENTICATE_NTLM_TYPE2MSG:
      result = imap_state_auth_ntlm_type2msg_resp(conn, imapcode,
                                                  imapc->state);
      break;
#endif

    case IMAP_AUTHENTICATE_XOAUTH2:
      result = imap_state_auth_xoauth2_resp(conn, imapcode, imapc->state);
      break;

    case IMAP_AUTHENTICATE_CANCEL:
      result = imap_state_auth_cancel_resp(conn, imapcode, imapc->state);
      break;

    case IMAP_AUTHENTICATE_FINAL:
      result = imap_state_auth_final_resp(conn, imapcode, imapc->state);
      break;

    case IMAP_LOGIN:
      result = imap_state_login_resp(conn, imapcode, imapc->state);
      break;

    case IMAP_LIST:
      result = imap_state_list_resp(conn, imapcode, imapc->state);
      break;

    case IMAP_SELECT:
      result = imap_state_select_resp(conn, imapcode, imapc->state);
      break;

    case IMAP_FETCH:
      result = imap_state_fetch_resp(conn, imapcode, imapc->state);
      break;

    case IMAP_FETCH_FINAL:
      result = imap_state_fetch_final_resp(conn, imapcode, imapc->state);
      break;

    case IMAP_APPEND:
      result = imap_state_append_resp(conn, imapcode, imapc->state);
      break;

    case IMAP_APPEND_FINAL:
      result = imap_state_append_final_resp(conn, imapcode, imapc->state);
      break;

    case IMAP_LOGOUT:
      /* fallthrough, just stop! */
    default:
      /* internal error */
      state(conn, IMAP_STOP);
      break;
    }
  } while(!result && imapc->state != IMAP_STOP && Curl_pp_moredata(pp));

  return result;
}