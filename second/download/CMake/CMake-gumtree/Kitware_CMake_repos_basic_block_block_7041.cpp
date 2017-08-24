{
  ssize_t written = -1;
  struct Curl_easy *data = conn->data;
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  SecBuffer outbuf;
  SecBufferDesc outbuf_desc;
  SecBuffer inbuf;
  SecBufferDesc inbuf_desc;
#ifdef HAS_ALPN
  unsigned char alpn_buffer[128];
#endif
  SCHANNEL_CRED schannel_cred;
  SECURITY_STATUS sspi_status = SEC_E_OK;
  struct curl_schannel_cred *old_cred = NULL;
  struct in_addr addr;
#ifdef ENABLE_IPV6
  struct in6_addr addr6;
#endif
  TCHAR *host_name;
  CURLcode result;
  char * const hostname = SSL_IS_PROXY() ? conn->http_proxy.host.name :
    conn->host.name;

  infof(data, "schannel: SSL/TLS connection with %s port %hu (step 1/3)\n",
        hostname, conn->remote_port);

  if(Curl_verify_windows_version(5, 1, PLATFORM_WINNT,
                                 VERSION_LESS_THAN_EQUAL)) {
     /* SChannel in Windows XP (OS version 5.1) uses legacy handshakes and
        algorithms that may not be supported by all servers. */
     infof(data, "schannel: WinSSL version is old and may not be able to "
           "connect to some servers due to lack of SNI, algorithms, etc.\n");
  }

#ifdef HAS_ALPN
  /* ALPN is only supported on Windows 8.1 / Server 2012 R2 and above.
     Also it doesn't seem to be supported for Wine, see curl bug #983. */
  connssl->use_alpn = conn->bits.tls_enable_alpn &&
                      !GetProcAddress(GetModuleHandleA("ntdll"),
                                      "wine_get_version") &&
                      Curl_verify_windows_version(6, 3, PLATFORM_WINNT,
                                                  VERSION_GREATER_THAN_EQUAL);
#else
  connssl->use_alpn = false;
#endif

  connssl->cred = NULL;

  /* check for an existing re-usable credential handle */
  if(SSL_SET_OPTION(primary.sessionid)) {
    Curl_ssl_sessionid_lock(conn);
    if(!Curl_ssl_getsessionid(conn, (void **)&old_cred, NULL, sockindex)) {
      connssl->cred = old_cred;
      infof(data, "schannel: re-using existing credential handle\n");

      /* increment the reference counter of the credential/session handle */
      connssl->cred->refcount++;
      infof(data, "schannel: incremented credential handle refcount = %d\n",
            connssl->cred->refcount);
    }
    Curl_ssl_sessionid_unlock(conn);
  }

  if(!connssl->cred) {
    /* setup Schannel API options */
    memset(&schannel_cred, 0, sizeof(schannel_cred));
    schannel_cred.dwVersion = SCHANNEL_CRED_VERSION;

    if(conn->ssl_config.verifypeer) {
#ifdef _WIN32_WCE
      /* certificate validation on CE doesn't seem to work right; we'll
         do it following a more manual process. */
      schannel_cred.dwFlags = SCH_CRED_MANUAL_CRED_VALIDATION |
        SCH_CRED_IGNORE_NO_REVOCATION_CHECK |
        SCH_CRED_IGNORE_REVOCATION_OFFLINE;
#else
      schannel_cred.dwFlags = SCH_CRED_AUTO_CRED_VALIDATION;
      /* TODO s/data->set.ssl.no_revoke/SSL_SET_OPTION(no_revoke)/g */
      if(data->set.ssl.no_revoke)
        schannel_cred.dwFlags |= SCH_CRED_IGNORE_NO_REVOCATION_CHECK |
                                 SCH_CRED_IGNORE_REVOCATION_OFFLINE;
      else
        schannel_cred.dwFlags |= SCH_CRED_REVOCATION_CHECK_CHAIN;
#endif
      if(data->set.ssl.no_revoke)
        infof(data, "schannel: disabled server certificate revocation "
                    "checks\n");
      else
        infof(data, "schannel: checking server certificate revocation\n");
    }
    else {
      schannel_cred.dwFlags = SCH_CRED_MANUAL_CRED_VALIDATION |
        SCH_CRED_IGNORE_NO_REVOCATION_CHECK |
        SCH_CRED_IGNORE_REVOCATION_OFFLINE;
      infof(data, "schannel: disabled server certificate revocation checks\n");
    }

    if(!conn->ssl_config.verifyhost) {
      schannel_cred.dwFlags |= SCH_CRED_NO_SERVERNAME_CHECK;
      infof(data, "schannel: verifyhost setting prevents Schannel from "
            "comparing the supplied target name with the subject "
            "names in server certificates.\n");
    }

    switch(conn->ssl_config.version) {
    case CURL_SSLVERSION_DEFAULT:
    case CURL_SSLVERSION_TLSv1:
      schannel_cred.grbitEnabledProtocols = SP_PROT_TLS1_0_CLIENT |
        SP_PROT_TLS1_1_CLIENT |
        SP_PROT_TLS1_2_CLIENT;
      break;
    case CURL_SSLVERSION_TLSv1_0:
    case CURL_SSLVERSION_TLSv1_1:
    case CURL_SSLVERSION_TLSv1_2:
    case CURL_SSLVERSION_TLSv1_3:
      {
        result = set_ssl_version_min_max(&schannel_cred, conn);
        if(result != CURLE_OK)
          return result;
        break;
      }
    case CURL_SSLVERSION_SSLv3:
      schannel_cred.grbitEnabledProtocols = SP_PROT_SSL3_CLIENT;
      break;
    case CURL_SSLVERSION_SSLv2:
      schannel_cred.grbitEnabledProtocols = SP_PROT_SSL2_CLIENT;
      break;
    default:
      failf(data, "Unrecognized parameter passed via CURLOPT_SSLVERSION");
      return CURLE_SSL_CONNECT_ERROR;
    }

    /* allocate memory for the re-usable credential handle */
    connssl->cred = (struct curl_schannel_cred *)
      malloc(sizeof(struct curl_schannel_cred));
    if(!connssl->cred) {
      failf(data, "schannel: unable to allocate memory");
      return CURLE_OUT_OF_MEMORY;
    }
    memset(connssl->cred, 0, sizeof(struct curl_schannel_cred));
    connssl->cred->refcount = 1;

    /* https://msdn.microsoft.com/en-us/library/windows/desktop/aa374716.aspx
       */
    sspi_status =
      s_pSecFn->AcquireCredentialsHandle(NULL, (TCHAR *)UNISP_NAME,
                                         SECPKG_CRED_OUTBOUND, NULL,
                                         &schannel_cred, NULL, NULL,
                                         &connssl->cred->cred_handle,
                                         &connssl->cred->time_stamp);

    if(sspi_status != SEC_E_OK) {
      if(sspi_status == SEC_E_WRONG_PRINCIPAL)
        failf(data, "schannel: SNI or certificate check failed: %s",
              Curl_sspi_strerror(conn, sspi_status));
      else
        failf(data, "schannel: AcquireCredentialsHandle failed: %s",
              Curl_sspi_strerror(conn, sspi_status));
      Curl_safefree(connssl->cred);
      return CURLE_SSL_CONNECT_ERROR;
    }
  }

  /* Warn if SNI is disabled due to use of an IP address */
  if(Curl_inet_pton(AF_INET, hostname, &addr)
#ifdef ENABLE_IPV6
     || Curl_inet_pton(AF_INET6, hostname, &addr6)
#endif
    ) {
    infof(data, "schannel: using IP address, SNI is not supported by OS.\n");
  }

#ifdef HAS_ALPN
  if(connssl->use_alpn) {
    int cur = 0;
    int list_start_index = 0;
    unsigned int *extension_len = NULL;
    unsigned short* list_len = NULL;

    /* The first four bytes will be an unsigned int indicating number
       of bytes of data in the rest of the the buffer. */
    extension_len = (unsigned int *)(&alpn_buffer[cur]);
    cur += sizeof(unsigned int);

    /* The next four bytes are an indicator that this buffer will contain
       ALPN data, as opposed to NPN, for example. */
    *(unsigned int *)&alpn_buffer[cur] =
      SecApplicationProtocolNegotiationExt_ALPN;
    cur += sizeof(unsigned int);

    /* The next two bytes will be an unsigned short indicating the number
       of bytes used to list the preferred protocols. */
    list_len = (unsigned short*)(&alpn_buffer[cur]);
    cur += sizeof(unsigned short);

    list_start_index = cur;

#ifdef USE_NGHTTP2
    if(data->set.httpversion >= CURL_HTTP_VERSION_2) {
      memcpy(&alpn_buffer[cur], NGHTTP2_PROTO_ALPN, NGHTTP2_PROTO_ALPN_LEN);
      cur += NGHTTP2_PROTO_ALPN_LEN;
      infof(data, "schannel: ALPN, offering %s\n", NGHTTP2_PROTO_VERSION_ID);
    }
#endif

    alpn_buffer[cur++] = ALPN_HTTP_1_1_LENGTH;
    memcpy(&alpn_buffer[cur], ALPN_HTTP_1_1, ALPN_HTTP_1_1_LENGTH);
    cur += ALPN_HTTP_1_1_LENGTH;
    infof(data, "schannel: ALPN, offering %s\n", ALPN_HTTP_1_1);

    *list_len = curlx_uitous(cur - list_start_index);
    *extension_len = *list_len + sizeof(unsigned int) + sizeof(unsigned short);

    InitSecBuffer(&inbuf, SECBUFFER_APPLICATION_PROTOCOLS, alpn_buffer, cur);
    InitSecBufferDesc(&inbuf_desc, &inbuf, 1);
  }
  else
  {
    InitSecBuffer(&inbuf, SECBUFFER_EMPTY, NULL, 0);
    InitSecBufferDesc(&inbuf_desc, &inbuf, 1);
  }
#else /* HAS_ALPN */
  InitSecBuffer(&inbuf, SECBUFFER_EMPTY, NULL, 0);
  InitSecBufferDesc(&inbuf_desc, &inbuf, 1);
#endif

  /* setup output buffer */
  InitSecBuffer(&outbuf, SECBUFFER_EMPTY, NULL, 0);
  InitSecBufferDesc(&outbuf_desc, &outbuf, 1);

  /* setup request flags */
  connssl->req_flags = ISC_REQ_SEQUENCE_DETECT | ISC_REQ_REPLAY_DETECT |
    ISC_REQ_CONFIDENTIALITY | ISC_REQ_ALLOCATE_MEMORY |
    ISC_REQ_STREAM;

  /* allocate memory for the security context handle */
  connssl->ctxt = (struct curl_schannel_ctxt *)
    malloc(sizeof(struct curl_schannel_ctxt));
  if(!connssl->ctxt) {
    failf(data, "schannel: unable to allocate memory");
    return CURLE_OUT_OF_MEMORY;
  }
  memset(connssl->ctxt, 0, sizeof(struct curl_schannel_ctxt));

  host_name = Curl_convert_UTF8_to_tchar(hostname);
  if(!host_name)
    return CURLE_OUT_OF_MEMORY;

  /* Schannel InitializeSecurityContext:
     https://msdn.microsoft.com/en-us/library/windows/desktop/aa375924.aspx

     At the moment we don't pass inbuf unless we're using ALPN since we only
     use it for that, and Wine (for which we currently disable ALPN) is giving
     us problems with inbuf regardless. https://github.com/curl/curl/issues/983
  */
  sspi_status = s_pSecFn->InitializeSecurityContext(
    &connssl->cred->cred_handle, NULL, host_name, connssl->req_flags, 0, 0,
    (connssl->use_alpn ? &inbuf_desc : NULL),
    0, &connssl->ctxt->ctxt_handle,
    &outbuf_desc, &connssl->ret_flags, &connssl->ctxt->time_stamp);

  Curl_unicodefree(host_name);

  if(sspi_status != SEC_I_CONTINUE_NEEDED) {
    if(sspi_status == SEC_E_WRONG_PRINCIPAL)
      failf(data, "schannel: SNI or certificate check failed: %s",
            Curl_sspi_strerror(conn, sspi_status));
    else
      failf(data, "schannel: initial InitializeSecurityContext failed: %s",
            Curl_sspi_strerror(conn, sspi_status));
    Curl_safefree(connssl->ctxt);
    return CURLE_SSL_CONNECT_ERROR;
  }

  infof(data, "schannel: sending initial handshake data: "
        "sending %lu bytes...\n", outbuf.cbBuffer);

  /* send initial handshake data which is now stored in output buffer */
  result = Curl_write_plain(conn, conn->sock[sockindex], outbuf.pvBuffer,
                            outbuf.cbBuffer, &written);
  s_pSecFn->FreeContextBuffer(outbuf.pvBuffer);
  if((result != CURLE_OK) || (outbuf.cbBuffer != (size_t) written)) {
    failf(data, "schannel: failed to send initial handshake data: "
          "sent %zd of %lu bytes", written, outbuf.cbBuffer);
    return CURLE_SSL_CONNECT_ERROR;
  }

  infof(data, "schannel: sent initial handshake data: "
        "sent %zd bytes\n", written);

  connssl->recv_unrecoverable_err = CURLE_OK;
  connssl->recv_sspi_close_notify = false;
  connssl->recv_connection_closed = false;
  connssl->encdata_is_incomplete = false;

  /* continue to second handshake step */
  connssl->connecting_state = ssl_connect_2;

  return CURLE_OK;
}