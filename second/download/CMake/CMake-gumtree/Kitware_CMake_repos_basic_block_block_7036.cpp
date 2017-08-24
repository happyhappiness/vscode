r(; i <= (ssl_version_max >> 16); ++i) {
    switch(i) {
      case CURL_SSLVERSION_TLSv1_0:
        schannel_cred->grbitEnabledProtocols |= SP_PROT_TLS1_0_CLIENT;
        break;
      case CURL_SSLVERSION_TLSv1_1:
        schannel_cred->grbitEnabledProtocols |= SP_PROT_TLS1_1_CLIENT;
        break;
      case CURL_SSLVERSION_TLSv1_2:
        schannel_cred->grbitEnabledProtocols |= SP_PROT_TLS1_2_CLIENT;
        break;
      case CURL_SSLVERSION_TLSv1_3:
        failf(data, "Schannel: TLS 1.3 is not yet supported");
        return CURLE_SSL_CONNECT_ERROR;
    }
  }