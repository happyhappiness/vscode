{
      case CURL_SSLVERSION_TLSv1_0:
        protocol_priority[protocol_priority_idx++] = GNUTLS_TLS1_0;
        break;
      case CURL_SSLVERSION_TLSv1_1:
        protocol_priority[protocol_priority_idx++] = GNUTLS_TLS1_1;
        break;
      case CURL_SSLVERSION_TLSv1_2:
        protocol_priority[protocol_priority_idx++] = GNUTLS_TLS1_2;
        break;
      case CURL_SSLVERSION_TLSv1_3:
        failf(data, "GnuTLS: TLS 1.3 is not yet supported");
        return CURLE_SSL_CONNECT_ERROR;
    }