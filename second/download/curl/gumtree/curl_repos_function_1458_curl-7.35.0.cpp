static CURLcode pop3_statemach_act(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  curl_socket_t sock = conn->sock[FIRSTSOCKET];
  int pop3code;
  struct pop3_conn *pop3c = &conn->proto.pop3c;
  struct pingpong *pp = &pop3c->pp;
  size_t nread = 0;

  /* Busy upgrading the connection; right now all I/O is SSL/TLS, not POP3 */
  if(pop3c->state == POP3_UPGRADETLS)
    return pop3_perform_upgrade_tls(conn);

  /* Flush any data that needs to be sent */
  if(pp->sendleft)
    return Curl_pp_flushsend(pp);

 do {
    /* Read the response from the server */
    result = Curl_pp_readresp(sock, pp, &pop3code, &nread);
    if(result)
      return result;

    if(!pop3code)
      break;

    /* We have now received a full POP3 server response */
    switch(pop3c->state) {
    case POP3_SERVERGREET:
      result = pop3_state_servergreet_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_CAPA:
      result = pop3_state_capa_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_STARTTLS:
      result = pop3_state_starttls_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_AUTH_PLAIN:
      result = pop3_state_auth_plain_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_AUTH_LOGIN:
      result = pop3_state_auth_login_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_AUTH_LOGIN_PASSWD:
      result = pop3_state_auth_login_password_resp(conn, pop3code,
                                                   pop3c->state);
      break;

#ifndef CURL_DISABLE_CRYPTO_AUTH
    case POP3_AUTH_CRAMMD5:
      result = pop3_state_auth_cram_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_AUTH_DIGESTMD5:
      result = pop3_state_auth_digest_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_AUTH_DIGESTMD5_RESP:
      result = pop3_state_auth_digest_resp_resp(conn, pop3code, pop3c->state);
      break;
#endif

#ifdef USE_NTLM
    case POP3_AUTH_NTLM:
      result = pop3_state_auth_ntlm_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_AUTH_NTLM_TYPE2MSG:
      result = pop3_state_auth_ntlm_type2msg_resp(conn, pop3code,
                                                  pop3c->state);
      break;
#endif

    case POP3_AUTH_XOAUTH2:
      result = pop3_state_auth_xoauth2_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_AUTH_CANCEL:
      result = pop3_state_auth_cancel_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_AUTH_FINAL:
      result = pop3_state_auth_final_resp(conn, pop3code, pop3c->state);
      break;

#ifndef CURL_DISABLE_CRYPTO_AUTH
    case POP3_APOP:
      result = pop3_state_apop_resp(conn, pop3code, pop3c->state);
      break;
#endif

    case POP3_USER:
      result = pop3_state_user_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_PASS:
      result = pop3_state_pass_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_COMMAND:
      result = pop3_state_command_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_QUIT:
      /* fallthrough, just stop! */
    default:
      /* internal error */
      state(conn, POP3_STOP);
      break;
    }
  } while(!result && pop3c->state != POP3_STOP && Curl_pp_moredata(pp));

  return result;
}