static CURLcode
schannel_connect_step1(struct connectdata *conn, int sockindex)
{
  ssize_t written = -1;
  struct SessionHandle *data = conn->data;
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  SecBuffer outbuf;
  SecBufferDesc outbuf_desc;
  SCHANNEL_CRED schannel_cred;
  SECURITY_STATUS sspi_status = SEC_E_OK;
  struct curl_schannel_cred *old_cred = NULL;
  struct in_addr addr;
#ifdef ENABLE_IPV6
  struct in6_addr addr6;
#endif
  TCHAR *host_name;
  CURLcode result;

  infof(data, "schannel: SSL/TLS connection with %s port %hu (step 1/3)\n",
        conn->host.name, conn->remote_port);

  /* check for an existing re-usable credential handle */
  if(!Curl_ssl_getsessionid(conn, (void **)&old_cred, NULL)) {
    connssl->cred = old_cred;
    infof(data, "schannel: re-using existing credential handle\n");
  }
  else {
    /* setup Schannel API options */
    memset(&schannel_cred, 0, sizeof(schannel_cred));
    schannel_cred.dwVersion = SCHANNEL_CRED_VERSION;

    if(data->set.ssl.verifypeer) {
#ifdef _WIN32_WCE
      /* certificate validation on CE doesn't seem to work right; we'll
         do it following a more manual process. */
      schannel_cred.dwFlags = SCH_CRED_MANUAL_CRED_VALIDATION |
                              SCH_CRED_IGNORE_NO_REVOCATION_CHECK |
                              SCH_CRED_IGNORE_REVOCATION_OFFLINE;
#else
      schannel_cred.dwFlags = SCH_CRED_AUTO_CRED_VALIDATION |
                              SCH_CRED_REVOCATION_CHECK_CHAIN;
#endif
      infof(data, "schannel: checking server certificate revocation\n");
    }
    else {
      schannel_cred.dwFlags = SCH_CRED_MANUAL_CRED_VALIDATION |
                              SCH_CRED_IGNORE_NO_REVOCATION_CHECK |
                              SCH_CRED_IGNORE_REVOCATION_OFFLINE;
      infof(data, "schannel: disable server certificate revocation checks\n");
    }

    if(!data->set.ssl.verifyhost) {
      schannel_cred.dwFlags |= SCH_CRED_NO_SERVERNAME_CHECK;
      infof(data, "schannel: verifyhost setting prevents Schannel from "
                  "comparing the supplied target name with the subject "
                  "names in server certificates. Also disables SNI.\n");
    }

    switch(data->set.ssl.version) {
      default:
      case CURL_SSLVERSION_DEFAULT:
      case CURL_SSLVERSION_TLSv1:
        schannel_cred.grbitEnabledProtocols = SP_PROT_TLS1_0_CLIENT |
                                              SP_PROT_TLS1_1_CLIENT |
                                              SP_PROT_TLS1_2_CLIENT;
        break;
      case CURL_SSLVERSION_TLSv1_0:
        schannel_cred.grbitEnabledProtocols = SP_PROT_TLS1_0_CLIENT;
        break;
      case CURL_SSLVERSION_TLSv1_1:
        schannel_cred.grbitEnabledProtocols = SP_PROT_TLS1_1_CLIENT;
        break;
      case CURL_SSLVERSION_TLSv1_2:
        schannel_cred.grbitEnabledProtocols = SP_PROT_TLS1_2_CLIENT;
        break;
      case CURL_SSLVERSION_SSLv3:
        schannel_cred.grbitEnabledProtocols = SP_PROT_SSL3_CLIENT;
        break;
      case CURL_SSLVERSION_SSLv2:
        schannel_cred.grbitEnabledProtocols = SP_PROT_SSL2_CLIENT;
        break;
    }

    /* allocate memory for the re-usable credential handle */
    connssl->cred = (struct curl_schannel_cred *)
                     malloc(sizeof(struct curl_schannel_cred));
    if(!connssl->cred) {
      failf(data, "schannel: unable to allocate memory");
      return CURLE_OUT_OF_MEMORY;
    }
    memset(connssl->cred, 0, sizeof(struct curl_schannel_cred));

    /* http://msdn.microsoft.com/en-us/library/windows/desktop/aa374716.aspx */
    sspi_status = s_pSecFn->AcquireCredentialsHandle(NULL, (TCHAR *)UNISP_NAME,
      SECPKG_CRED_OUTBOUND, NULL, &schannel_cred, NULL, NULL,
      &connssl->cred->cred_handle, &connssl->cred->time_stamp);

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
  if(Curl_inet_pton(AF_INET, conn->host.name, &addr)
#ifdef ENABLE_IPV6
     || Curl_inet_pton(AF_INET6, conn->host.name, &addr6)
#endif
    ) {
    infof(data, "schannel: using IP address, SNI is not supported by OS.\n");
  }

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

  host_name = Curl_convert_UTF8_to_tchar(conn->host.name);
  if(!host_name)
    return CURLE_OUT_OF_MEMORY;

  /* http://msdn.microsoft.com/en-us/library/windows/desktop/aa375924.aspx */

  sspi_status = s_pSecFn->InitializeSecurityContext(
    &connssl->cred->cred_handle, NULL, host_name,
    connssl->req_flags, 0, 0, NULL, 0, &connssl->ctxt->ctxt_handle,
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

  /* continue to second handshake step */
  connssl->connecting_state = ssl_connect_2;

  return CURLE_OK;
}