{
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