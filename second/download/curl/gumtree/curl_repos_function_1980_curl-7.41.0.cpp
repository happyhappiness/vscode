CURLcode Curl_sasl_continue(struct SASL *sasl, struct connectdata *conn,
                            int code, saslprogress *progress)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  saslstate newstate = SASL_FINAL;
  char *resp = NULL;
#if !defined(CURL_DISABLE_CRYPTO_AUTH)
  char *serverdata;
  char *chlg = NULL;
  size_t chlglen = 0;
#endif
  size_t len = 0;

  *progress = SASL_INPROGRESS;

  if(sasl->state == SASL_FINAL) {
    if(code != sasl->params->finalcode)
      result = CURLE_LOGIN_DENIED;
    *progress = SASL_DONE;
    state(sasl, conn, SASL_STOP);
    return result;
  }

  if(sasl->state != SASL_CANCEL && code != sasl->params->contcode) {
    *progress = SASL_DONE;
    state(sasl, conn, SASL_STOP);
    return CURLE_LOGIN_DENIED;
  }

  switch(sasl->state) {
  case SASL_STOP:
    *progress = SASL_DONE;
    return result;
  case SASL_PLAIN:
    result = sasl_create_plain_message(data, conn->user, conn->passwd, &resp,
                                       &len);
    break;
  case SASL_LOGIN:
    result = sasl_create_login_message(data, conn->user, &resp, &len);
    newstate = SASL_LOGIN_PASSWD;
    break;
  case SASL_LOGIN_PASSWD:
    result = sasl_create_login_message(data, conn->passwd, &resp, &len);
    break;
  case SASL_EXTERNAL:
    result = sasl_create_external_message(data, conn->user, &resp, &len);
    break;

#ifndef CURL_DISABLE_CRYPTO_AUTH
  case SASL_CRAMMD5:
    sasl->params->getmessage(data->state.buffer, &serverdata);
    result = sasl_decode_cram_md5_message(serverdata, &chlg, &chlglen);
    if(!result)
      result = sasl_create_cram_md5_message(data, chlg, conn->user,
                                            conn->passwd, &resp, &len);
    Curl_safefree(chlg);
    break;
  case SASL_DIGESTMD5:
    sasl->params->getmessage(data->state.buffer, &serverdata);
    result = Curl_sasl_create_digest_md5_message(data, serverdata,
                                                 conn->user, conn->passwd,
                                                 sasl->params->service,
                                                 &resp, &len);
    newstate = SASL_DIGESTMD5_RESP;
    break;
  case SASL_DIGESTMD5_RESP:
    if(!(resp = strdup("")))
      result = CURLE_OUT_OF_MEMORY;
    break;
#endif

#ifdef USE_NTLM
  case SASL_NTLM:
    /* Create the type-1 message */
    result = Curl_sasl_create_ntlm_type1_message(conn->user, conn->passwd,
                                                 &conn->ntlm, &resp, &len);
    newstate = SASL_NTLM_TYPE2MSG;
    break;
  case SASL_NTLM_TYPE2MSG:
    /* Decode the type-2 message */
    sasl->params->getmessage(data->state.buffer, &serverdata);
    result = Curl_sasl_decode_ntlm_type2_message(data, serverdata,
                                                 &conn->ntlm);
    if(!result)
      result = Curl_sasl_create_ntlm_type3_message(data, conn->user,
                                                   conn->passwd, &conn->ntlm,
                                                   &resp, &len);
    break;
#endif

#if defined(USE_KERBEROS5)
  case SASL_GSSAPI:
    result = Curl_sasl_create_gssapi_user_message(data, conn->user,
                                                  conn->passwd,
                                                  sasl->params->service,
                                                  sasl->mutual_auth, NULL,
                                                  &conn->krb5,
                                                  &resp, &len);
    newstate = SASL_GSSAPI_TOKEN;
    break;
  case SASL_GSSAPI_TOKEN:
    sasl->params->getmessage(data->state.buffer, &serverdata);
    if(sasl->mutual_auth) {
      /* Decode the user token challenge and create the optional response
         message */
      result = Curl_sasl_create_gssapi_user_message(data, NULL, NULL, NULL,
                                                    sasl->mutual_auth,
                                                    serverdata, &conn->krb5,
                                                    &resp, &len);
      newstate = SASL_GSSAPI_NO_DATA;
    }
    else
      /* Decode the security challenge and create the response message */
      result = Curl_sasl_create_gssapi_security_message(data, serverdata,
                                                        &conn->krb5,
                                                        &resp, &len);
    break;
  case SASL_GSSAPI_NO_DATA:
    sasl->params->getmessage(data->state.buffer, &serverdata);
    /* Decode the security challenge and create the response message */
    result = Curl_sasl_create_gssapi_security_message(data, serverdata,
                                                      &conn->krb5,
                                                      &resp, &len);
    break;
#endif

  case SASL_XOAUTH2:
    /* Create the authorisation message */
    result = sasl_create_xoauth2_message(data, conn->user,
                                         conn->xoauth2_bearer, &resp, &len);
    break;
  case SASL_CANCEL:
    /* Remove the offending mechanism from the supported list */
    sasl->authmechs ^= sasl->authused;

    /* Start an alternative SASL authentication */
    result = Curl_sasl_start(sasl, conn, sasl->force_ir, progress);
    newstate = sasl->state;   /* Use state from Curl_sasl_start() */
    break;
  default:
    failf(data, "Unsupported SASL authentication mechanism");
    result = CURLE_UNSUPPORTED_PROTOCOL;  /* Should not happen */
    break;
  }

  switch(result) {
  case CURLE_BAD_CONTENT_ENCODING:
    /* Cancel dialog */
    result = sasl->params->sendcont(conn, "*");
    newstate = SASL_CANCEL;
    break;
  case CURLE_OK:
    if(resp)
      result = sasl->params->sendcont(conn, resp);
    break;
  default:
    newstate = SASL_STOP;    /* Stop on error */
    *progress = SASL_DONE;
    break;
  }

  Curl_safefree(resp);

  state(sasl, conn, newstate);

  return result;
}