static CURLcode smtp_statemach_act(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  curl_socket_t sock = conn->sock[FIRSTSOCKET];
  struct SessionHandle *data = conn->data;
  int smtpcode;
  struct smtp_conn *smtpc = &conn->proto.smtpc;
  struct pingpong *pp = &smtpc->pp;
  size_t nread = 0;

  /* Busy upgrading the connection; right now all I/O is SSL/TLS, not SMTP */
  if(smtpc->state == SMTP_UPGRADETLS)
    return smtp_perform_upgrade_tls(conn);

  /* Flush any data that needs to be sent */
  if(pp->sendleft)
    return Curl_pp_flushsend(pp);

  do {
    /* Read the response from the server */
    result = Curl_pp_readresp(sock, pp, &smtpcode, &nread);
    if(result)
      return result;

    /* Store the latest response for later retrieval if necessary */
    if(smtpc->state != SMTP_QUIT && smtpcode != 1)
      data->info.httpcode = smtpcode;

    if(!smtpcode)
      break;

    /* We have now received a full SMTP server response */
    switch(smtpc->state) {
    case SMTP_SERVERGREET:
      result = smtp_state_servergreet_resp(conn, smtpcode, smtpc->state);
      break;

    case SMTP_EHLO:
      result = smtp_state_ehlo_resp(conn, smtpcode, smtpc->state);
      break;

    case SMTP_HELO:
      result = smtp_state_helo_resp(conn, smtpcode, smtpc->state);
      break;

    case SMTP_STARTTLS:
      result = smtp_state_starttls_resp(conn, smtpcode, smtpc->state);
      break;

    case SMTP_AUTH_PLAIN:
      result = smtp_state_auth_plain_resp(conn, smtpcode, smtpc->state);
      break;

    case SMTP_AUTH_LOGIN:
      result = smtp_state_auth_login_resp(conn, smtpcode, smtpc->state);
      break;

    case SMTP_AUTH_LOGIN_PASSWD:
      result = smtp_state_auth_login_password_resp(conn, smtpcode,
                                                   smtpc->state);
      break;

#ifndef CURL_DISABLE_CRYPTO_AUTH
    case SMTP_AUTH_CRAMMD5:
      result = smtp_state_auth_cram_resp(conn, smtpcode, smtpc->state);
      break;

    case SMTP_AUTH_DIGESTMD5:
      result = smtp_state_auth_digest_resp(conn, smtpcode, smtpc->state);
      break;

    case SMTP_AUTH_DIGESTMD5_RESP:
      result = smtp_state_auth_digest_resp_resp(conn, smtpcode, smtpc->state);
      break;
#endif

#ifdef USE_NTLM
    case SMTP_AUTH_NTLM:
      result = smtp_state_auth_ntlm_resp(conn, smtpcode, smtpc->state);
      break;

    case SMTP_AUTH_NTLM_TYPE2MSG:
      result = smtp_state_auth_ntlm_type2msg_resp(conn, smtpcode,
                                                  smtpc->state);
      break;
#endif

    case SMTP_AUTH_XOAUTH2:
      result = smtp_state_auth_xoauth2_resp(conn, smtpcode, smtpc->state);
      break;

    case SMTP_AUTH_CANCEL:
      result = smtp_state_auth_cancel_resp(conn, smtpcode, smtpc->state);
      break;

    case SMTP_AUTH_FINAL:
      result = smtp_state_auth_final_resp(conn, smtpcode, smtpc->state);
      break;

    case SMTP_COMMAND:
      result = smtp_state_command_resp(conn, smtpcode, smtpc->state);
      break;

    case SMTP_MAIL:
      result = smtp_state_mail_resp(conn, smtpcode, smtpc->state);
      break;

    case SMTP_RCPT:
      result = smtp_state_rcpt_resp(conn, smtpcode, smtpc->state);
      break;

    case SMTP_DATA:
      result = smtp_state_data_resp(conn, smtpcode, smtpc->state);
      break;

    case SMTP_POSTDATA:
      result = smtp_state_postdata_resp(conn, smtpcode, smtpc->state);
      break;

    case SMTP_QUIT:
      /* fallthrough, just stop! */
    default:
      /* internal error */
      state(conn, SMTP_STOP);
      break;
    }
  } while(!result && smtpc->state != SMTP_STOP && Curl_pp_moredata(pp));

  return result;
}