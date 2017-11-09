static CURLcode verify_certificate(struct connectdata *conn, int sockindex)
{
  SECURITY_STATUS status;
  struct Curl_easy *data = conn->data;
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  CURLcode result = CURLE_OK;
  CERT_CONTEXT *pCertContextServer = NULL;
  const CERT_CHAIN_CONTEXT *pChainContext = NULL;
  const char * const conn_hostname = SSL_IS_PROXY() ?
    conn->http_proxy.host.name :
    conn->host.name;

  status = s_pSecFn->QueryContextAttributes(&BACKEND->ctxt->ctxt_handle,
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
                                (data->set.ssl.no_revoke ? 0 :
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
    if(conn->ssl_config.verifyhost) {
      TCHAR cert_hostname_buff[256];
      DWORD len;

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
                              CERT_NAME_DISABLE_IE4_UTF8_FLAG,
                              NULL,
                              cert_hostname_buff,
                              256);
      if(len > 0) {
        const char *cert_hostname;

        /* Comparing the cert name and the connection hostname encoded as UTF-8
         * is acceptable since both values are assumed to use ASCII
         * (or some equivalent) encoding
         */
        cert_hostname = Curl_convert_tchar_to_UTF8(cert_hostname_buff);
        if(!cert_hostname) {
          result = CURLE_OUT_OF_MEMORY;
        }
        else{
          int match_result;

          match_result = Curl_cert_hostcheck(cert_hostname, conn->host.name);
          if(match_result == CURL_HOST_MATCH) {
            infof(data,
                  "schannel: connection hostname (%s) validated "
                  "against certificate name (%s)\n",
                  conn->host.name,
                  cert_hostname);
            result = CURLE_OK;
          }
          else{
            failf(data,
                  "schannel: connection hostname (%s) "
                  "does not match certificate name (%s)",
                  conn->host.name,
                  cert_hostname);
            result = CURLE_PEER_FAILED_VERIFICATION;
          }
          Curl_unicodefree(cert_hostname);
        }
      }
      else {
        failf(data,
              "schannel: CertGetNameString did not provide any "
              "certificate name information");
        result = CURLE_PEER_FAILED_VERIFICATION;
      }
    }
  }

  if(pChainContext)
    CertFreeCertificateChain(pChainContext);

  if(pCertContextServer)
    CertFreeCertificateContext(pCertContextServer);

  return result;
}