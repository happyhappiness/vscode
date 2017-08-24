{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  SECURITY_STATUS sspi_status = SEC_E_OK;
  CERT_CONTEXT *ccert_context = NULL;
#ifndef CURL_DISABLE_VERBOSE_STRINGS
  const char * const hostname = SSL_IS_PROXY() ? conn->http_proxy.host.name :
    conn->host.name;
#endif
#ifdef HAS_ALPN
  SecPkgContext_ApplicationProtocol alpn_result;
#endif

  DEBUGASSERT(ssl_connect_3 == connssl->connecting_state);

  infof(data, "schannel: SSL/TLS connection with %s port %hu (step 3/3)\n",
        hostname, conn->remote_port);

  if(!connssl->cred)
    return CURLE_SSL_CONNECT_ERROR;

  /* check if the required context attributes are met */
  if(connssl->ret_flags != connssl->req_flags) {
    if(!(connssl->ret_flags & ISC_RET_SEQUENCE_DETECT))
      failf(data, "schannel: failed to setup sequence detection");
    if(!(connssl->ret_flags & ISC_RET_REPLAY_DETECT))
      failf(data, "schannel: failed to setup replay detection");
    if(!(connssl->ret_flags & ISC_RET_CONFIDENTIALITY))
      failf(data, "schannel: failed to setup confidentiality");
    if(!(connssl->ret_flags & ISC_RET_ALLOCATED_MEMORY))
      failf(data, "schannel: failed to setup memory allocation");
    if(!(connssl->ret_flags & ISC_RET_STREAM))
      failf(data, "schannel: failed to setup stream orientation");
    return CURLE_SSL_CONNECT_ERROR;
  }

#ifdef HAS_ALPN
  if(connssl->use_alpn) {
    sspi_status = s_pSecFn->QueryContextAttributes(&connssl->ctxt->ctxt_handle,
      SECPKG_ATTR_APPLICATION_PROTOCOL, &alpn_result);

    if(sspi_status != SEC_E_OK) {
      failf(data, "schannel: failed to retrieve ALPN result");
      return CURLE_SSL_CONNECT_ERROR;
    }

    if(alpn_result.ProtoNegoStatus ==
       SecApplicationProtocolNegotiationStatus_Success) {

      infof(data, "schannel: ALPN, server accepted to use %.*s\n",
        alpn_result.ProtocolIdSize, alpn_result.ProtocolId);

#ifdef USE_NGHTTP2
      if(alpn_result.ProtocolIdSize == NGHTTP2_PROTO_VERSION_ID_LEN &&
         !memcmp(NGHTTP2_PROTO_VERSION_ID, alpn_result.ProtocolId,
          NGHTTP2_PROTO_VERSION_ID_LEN)) {
        conn->negnpn = CURL_HTTP_VERSION_2;
      }
      else
#endif
      if(alpn_result.ProtocolIdSize == ALPN_HTTP_1_1_LENGTH &&
         !memcmp(ALPN_HTTP_1_1, alpn_result.ProtocolId,
           ALPN_HTTP_1_1_LENGTH)) {
        conn->negnpn = CURL_HTTP_VERSION_1_1;
      }
    }
    else
      infof(data, "ALPN, server did not agree to a protocol\n");
  }
#endif

  /* save the current session data for possible re-use */
  if(SSL_SET_OPTION(primary.sessionid)) {
    bool incache;
    struct curl_schannel_cred *old_cred = NULL;

    Curl_ssl_sessionid_lock(conn);
    incache = !(Curl_ssl_getsessionid(conn, (void **)&old_cred, NULL,
                                      sockindex));
    if(incache) {
      if(old_cred != connssl->cred) {
        infof(data, "schannel: old credential handle is stale, removing\n");
        /* we're not taking old_cred ownership here, no refcount++ is needed */
        Curl_ssl_delsessionid(conn, (void *)old_cred);
        incache = FALSE;
      }
    }
    if(!incache) {
      result = Curl_ssl_addsessionid(conn, (void *)connssl->cred,
                                     sizeof(struct curl_schannel_cred),
                                     sockindex);
      if(result) {
        Curl_ssl_sessionid_unlock(conn);
        failf(data, "schannel: failed to store credential handle");
        return result;
      }
      else {
        /* this cred session is now also referenced by sessionid cache */
        connssl->cred->refcount++;
        infof(data, "schannel: stored credential handle in session cache\n");
      }
    }
    Curl_ssl_sessionid_unlock(conn);
  }

  if(data->set.ssl.certinfo) {
    sspi_status = s_pSecFn->QueryContextAttributes(&connssl->ctxt->ctxt_handle,
      SECPKG_ATTR_REMOTE_CERT_CONTEXT, &ccert_context);

    if((sspi_status != SEC_E_OK) || (ccert_context == NULL)) {
      failf(data, "schannel: failed to retrieve remote cert context");
      return CURLE_SSL_CONNECT_ERROR;
    }

    result = Curl_ssl_init_certinfo(data, 1);
    if(!result) {
      if(((ccert_context->dwCertEncodingType & X509_ASN_ENCODING) != 0) &&
         (ccert_context->cbCertEncoded > 0)) {

        const char *beg = (const char *) ccert_context->pbCertEncoded;
        const char *end = beg + ccert_context->cbCertEncoded;
        result = Curl_extract_certinfo(conn, 0, beg, end);
      }
    }
    CertFreeCertificateContext(ccert_context);
    if(result)
      return result;
  }

  connssl->connecting_state = ssl_connect_done;

  return CURLE_OK;
}