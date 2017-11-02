CURLcode Curl_sasl_start(struct SASL *sasl, struct connectdata *conn,
                         bool force_ir, saslprogress *progress)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  unsigned int enabledmechs;
  const char *mech = NULL;
  char *resp = NULL;
  size_t len = 0;
  saslstate state1 = SASL_STOP;
  saslstate state2 = SASL_FINAL;

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
      result = sasl_create_external_message(data, conn->user, &resp, &len);
  }
  else if(conn->bits.user_passwd) {
#if defined(USE_KERBEROS5)
    if(enabledmechs & SASL_MECH_GSSAPI) {
      sasl->mutual_auth = FALSE; /* TODO: Calculate mutual authentication */
      mech = SASL_MECH_STRING_GSSAPI;
      state1 = SASL_GSSAPI;
      state2 = SASL_GSSAPI_TOKEN;
      sasl->authused = SASL_MECH_GSSAPI;

      if(force_ir || data->set.sasl_ir)
        result = Curl_sasl_create_gssapi_user_message(data, conn->user,
                                                      conn->passwd,
                                                      sasl->params->service,
                                                      sasl->mutual_auth,
                                                      NULL, &conn->krb5,
                                                      &resp, &len);
    }
    else
#endif
#ifndef CURL_DISABLE_CRYPTO_AUTH
    if(enabledmechs & SASL_MECH_DIGEST_MD5) {
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
    if(enabledmechs & SASL_MECH_NTLM) {
      mech = SASL_MECH_STRING_NTLM;
      state1 = SASL_NTLM;
      state2 = SASL_NTLM_TYPE2MSG;
      sasl->authused = SASL_MECH_NTLM;

      if(force_ir || data->set.sasl_ir)
        result = Curl_sasl_create_ntlm_type1_message(conn->user, conn->passwd,
                                                     &conn->ntlm, &resp, &len);
      }
    else
#endif
    if((enabledmechs & SASL_MECH_XOAUTH2) || conn->xoauth2_bearer) {
      mech = SASL_MECH_STRING_XOAUTH2;
      state1 = SASL_XOAUTH2;
      sasl->authused = SASL_MECH_XOAUTH2;

      if(force_ir || data->set.sasl_ir)
        result = sasl_create_xoauth2_message(data, conn->user,
                                             conn->xoauth2_bearer,
                                             &resp, &len);
    }
    else if(enabledmechs & SASL_MECH_LOGIN) {
      mech = SASL_MECH_STRING_LOGIN;
      state1 = SASL_LOGIN;
      state2 = SASL_LOGIN_PASSWD;
      sasl->authused = SASL_MECH_LOGIN;

      if(force_ir || data->set.sasl_ir)
        result = sasl_create_login_message(data, conn->user, &resp, &len);
    }
    else if(enabledmechs & SASL_MECH_PLAIN) {
      mech = SASL_MECH_STRING_PLAIN;
      state1 = SASL_PLAIN;
      sasl->authused = SASL_MECH_PLAIN;

      if(force_ir || data->set.sasl_ir)
        result = sasl_create_plain_message(data, conn->user, conn->passwd,
                                           &resp, &len);
    }
  }

  if(!result) {
    if(resp && sasl->params->maxirlen &&
       strlen(mech) + len > sasl->params->maxirlen) {
      Curl_safefree(resp);
      resp = NULL;
    }

    if(mech) {
      result = sasl->params->sendauth(conn, mech, resp);
      if(!result) {
        *progress = SASL_INPROGRESS;
        state(sasl, conn, resp? state2: state1);
      }
    }
  }

  Curl_safefree(resp);

  return result;
}