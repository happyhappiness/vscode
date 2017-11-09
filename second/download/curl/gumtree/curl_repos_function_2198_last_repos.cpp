CURLcode Curl_sasl_start(struct SASL *sasl, struct connectdata *conn,
                         bool force_ir, saslprogress *progress)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;
  unsigned int enabledmechs;
  const char *mech = NULL;
  char *resp = NULL;
  size_t len = 0;
  saslstate state1 = SASL_STOP;
  saslstate state2 = SASL_FINAL;
  const char * const hostname = SSL_IS_PROXY() ? conn->http_proxy.host.name :
    conn->host.name;
  const long int port = SSL_IS_PROXY() ? conn->port : conn->remote_port;
#if defined(USE_KERBEROS5)
  const char *service = data->set.str[STRING_SERVICE_NAME] ?
    data->set.str[STRING_SERVICE_NAME] :
    sasl->params->service;
#endif

  sasl->force_ir = force_ir;    /* Latch for future use */
  sasl->authused = 0;           /* No mechanism used yet */
  enabledmechs = sasl->authmechs & sasl->prefmech;
  *progress = SASL_IDLE;

  /* Calculate the supported authentication mechanism, by decreasing order of
     security, as well as the initial response where appropriate */
  if((enabledmechs & SASL_MECH_EXTERNAL) && !conn->passwd[0]) {
    mech = SASL_MECH_STRING_EXTERNAL;
    state1 = SASL_EXTERNAL;
    sasl->authused = SASL_MECH_EXTERNAL;

    if(force_ir || data->set.sasl_ir)
      result = Curl_auth_create_external_message(data, conn->user, &resp,
                                                 &len);
  }
  else if(conn->bits.user_passwd) {
#if defined(USE_KERBEROS5)
    if((enabledmechs & SASL_MECH_GSSAPI) && Curl_auth_is_gssapi_supported() &&
       Curl_auth_user_contains_domain(conn->user)) {
      sasl->mutual_auth = FALSE; /* TODO: Calculate mutual authentication */
      mech = SASL_MECH_STRING_GSSAPI;
      state1 = SASL_GSSAPI;
      state2 = SASL_GSSAPI_TOKEN;
      sasl->authused = SASL_MECH_GSSAPI;

      if(force_ir || data->set.sasl_ir)
        result = Curl_auth_create_gssapi_user_message(data, conn->user,
                                                      conn->passwd,
                                                      service,
                                                      data->easy_conn->
                                                            host.name,
                                                      sasl->mutual_auth,
                                                      NULL, &conn->krb5,
                                                      &resp, &len);
    }
    else
#endif
#ifndef CURL_DISABLE_CRYPTO_AUTH
    if((enabledmechs & SASL_MECH_DIGEST_MD5) &&
       Curl_auth_is_digest_supported()) {
      mech = SASL_MECH_STRING_DIGEST_MD5;
      state1 = SASL_DIGESTMD5;
      sasl->authused = SASL_MECH_DIGEST_MD5;
    }
    else if(enabledmechs & SASL_MECH_CRAM_MD5) {
      mech = SASL_MECH_STRING_CRAM_MD5;
      state1 = SASL_CRAMMD5;
      sasl->authused = SASL_MECH_CRAM_MD5;
    }
    else
#endif
#ifdef USE_NTLM
    if((enabledmechs & SASL_MECH_NTLM) && Curl_auth_is_ntlm_supported()) {
      mech = SASL_MECH_STRING_NTLM;
      state1 = SASL_NTLM;
      state2 = SASL_NTLM_TYPE2MSG;
      sasl->authused = SASL_MECH_NTLM;

      if(force_ir || data->set.sasl_ir)
        result = Curl_auth_create_ntlm_type1_message(data,
                                                     conn->user, conn->passwd,
                                                     &conn->ntlm, &resp, &len);
      }
    else
#endif
    if((enabledmechs & SASL_MECH_OAUTHBEARER) && conn->oauth_bearer) {
      mech = SASL_MECH_STRING_OAUTHBEARER;
      state1 = SASL_OAUTH2;
      state2 = SASL_OAUTH2_RESP;
      sasl->authused = SASL_MECH_OAUTHBEARER;

      if(force_ir || data->set.sasl_ir)
        result = Curl_auth_create_oauth_bearer_message(data, conn->user,
                                                       hostname,
                                                       port,
                                                       conn->oauth_bearer,
                                                       &resp, &len);
    }
    else if((enabledmechs & SASL_MECH_XOAUTH2) && conn->oauth_bearer) {
      mech = SASL_MECH_STRING_XOAUTH2;
      state1 = SASL_OAUTH2;
      sasl->authused = SASL_MECH_XOAUTH2;

      if(force_ir || data->set.sasl_ir)
        result = Curl_auth_create_oauth_bearer_message(data, conn->user,
                                                       NULL, 0,
                                                       conn->oauth_bearer,
                                                       &resp, &len);
    }
    else if(enabledmechs & SASL_MECH_LOGIN) {
      mech = SASL_MECH_STRING_LOGIN;
      state1 = SASL_LOGIN;
      state2 = SASL_LOGIN_PASSWD;
      sasl->authused = SASL_MECH_LOGIN;

      if(force_ir || data->set.sasl_ir)
        result = Curl_auth_create_login_message(data, conn->user, &resp, &len);
    }
    else if(enabledmechs & SASL_MECH_PLAIN) {
      mech = SASL_MECH_STRING_PLAIN;
      state1 = SASL_PLAIN;
      sasl->authused = SASL_MECH_PLAIN;

      if(force_ir || data->set.sasl_ir)
        result = Curl_auth_create_plain_message(data, conn->user, conn->passwd,
                                                &resp, &len);
    }
  }

  if(!result && mech) {
    if(resp && sasl->params->maxirlen &&
       strlen(mech) + len > sasl->params->maxirlen) {
      free(resp);
      resp = NULL;
    }

    result = sasl->params->sendauth(conn, mech, resp);
    if(!result) {
      *progress = SASL_INPROGRESS;
      state(sasl, conn, resp ? state2 : state1);
    }
  }

  free(resp);

  return result;
}