f(conn->ssl_config.verifyhost) {
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