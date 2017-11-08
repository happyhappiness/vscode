static CURLcode verify_certificate(struct connectdata *conn, int sockindex)
{
  SECURITY_STATUS status;
  struct Curl_easy *data = conn->data;
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  CURLcode result = CURLE_OK;
  CERT_CONTEXT *pCertContextServer = NULL;
  const CERT_CHAIN_CONTEXT *pChainContext = NULL;

  status = s_pSecFn->QueryContextAttributes(&connssl->ctxt->ctxt_handle,
                                            SECPKG_ATTR_REMOTE_CERT_CONTEXT,
                                            &pCertContextServer);

  if((status != SEC_E_OK) || (pCertContextServer == NULL)) {
    failf(data, "schannel: Failed to read remote certificate context: %s",
          Curl_sspi_strerror(conn, status));
    result = CURLE_PEER_FAILED_VERIFICATION;
  }

  if(result == CURLE_OK) {
    CERT_CHAIN_PARA ChainPara;
    memset(&ChainPara, 0, sizeof(ChainPara));
    ChainPara.cbSize = sizeof(ChainPara);

    if(!CertGetCertificateChain(NULL,
                                pCertContextServer,
                                NULL,
                                pCertContextServer->hCertStore,
                                &ChainPara,
                                (data->set.ssl_no_revoke ? 0 :
                                 CERT_CHAIN_REVOCATION_CHECK_CHAIN),
                                NULL,
                                &pChainContext)) {
      failf(data, "schannel: CertGetCertificateChain failed: %s",
            Curl_sspi_strerror(conn, GetLastError()));
      pChainContext = NULL;
      result = CURLE_PEER_FAILED_VERIFICATION;
    }

    if(result == CURLE_OK) {
      CERT_SIMPLE_CHAIN *pSimpleChain = pChainContext->rgpChain[0];
      DWORD dwTrustErrorMask = ~(DWORD)(CERT_TRUST_IS_NOT_TIME_NESTED);
      dwTrustErrorMask &= pSimpleChain->TrustStatus.dwErrorStatus;
      if(dwTrustErrorMask) {
        if(dwTrustErrorMask & CERT_TRUST_IS_REVOKED)
          failf(data, "schannel: CertGetCertificateChain trust error"
                " CERT_TRUST_IS_REVOKED");
        else if(dwTrustErrorMask & CERT_TRUST_IS_PARTIAL_CHAIN)
          failf(data, "schannel: CertGetCertificateChain trust error"
                " CERT_TRUST_IS_PARTIAL_CHAIN");
        else if(dwTrustErrorMask & CERT_TRUST_IS_UNTRUSTED_ROOT)
          failf(data, "schannel: CertGetCertificateChain trust error"
                " CERT_TRUST_IS_UNTRUSTED_ROOT");
        else if(dwTrustErrorMask & CERT_TRUST_IS_NOT_TIME_VALID)
          failf(data, "schannel: CertGetCertificateChain trust error"
                " CERT_TRUST_IS_NOT_TIME_VALID");
        else
          failf(data, "schannel: CertGetCertificateChain error mask: 0x%08x",
                dwTrustErrorMask);
        result = CURLE_PEER_FAILED_VERIFICATION;
      }
    }
  }

  if(result == CURLE_OK) {
    if(data->set.ssl.verifyhost) {
      TCHAR cert_hostname_buff[128];
      xcharp_u hostname;
      xcharp_u cert_hostname;
      DWORD len;

      cert_hostname.const_tchar_ptr = cert_hostname_buff;
      hostname.tchar_ptr = Curl_convert_UTF8_to_tchar(conn->host.name);

      /* TODO: Fix this for certificates with multiple alternative names.
      Right now we're only asking for the first preferred alternative name.
      Instead we'd need to do all via CERT_NAME_SEARCH_ALL_NAMES_FLAG
      (if WinCE supports that?) and run this section in a loop for each.
      https://msdn.microsoft.com/en-us/library/windows/desktop/aa376086.aspx
      curl: (51) schannel: CertGetNameString() certificate hostname
      (.google.com) did not match connection (google.com)
      */
      len = CertGetNameString(pCertContextServer,
                              CERT_NAME_DNS_TYPE,
                              0,
                              NULL,
                              cert_hostname.tchar_ptr,
                              128);
      if(len > 0 && *cert_hostname.tchar_ptr == '*') {
        /* this is a wildcard cert.  try matching the last len - 1 chars */
        int hostname_len = strlen(conn->host.name);
        cert_hostname.tchar_ptr++;
        if(_tcsicmp(cert_hostname.const_tchar_ptr,