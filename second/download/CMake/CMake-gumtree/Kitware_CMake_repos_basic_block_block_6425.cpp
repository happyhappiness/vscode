{
    /* TLS 1.0 with AES (RFC 3268) */
    case TLS_RSA_WITH_AES_128_CBC_SHA:
      return "TLS_RSA_WITH_AES_128_CBC_SHA";
      break;
    case TLS_DH_DSS_WITH_AES_128_CBC_SHA:
      return "TLS_DH_DSS_WITH_AES_128_CBC_SHA";
      break;
    case TLS_DH_RSA_WITH_AES_128_CBC_SHA:
      return "TLS_DH_RSA_WITH_AES_128_CBC_SHA";
      break;
    case TLS_DHE_DSS_WITH_AES_128_CBC_SHA:
      return "TLS_DHE_DSS_WITH_AES_128_CBC_SHA";
      break;
    case TLS_DHE_RSA_WITH_AES_128_CBC_SHA:
      return "TLS_DHE_RSA_WITH_AES_128_CBC_SHA";
      break;
    case TLS_DH_anon_WITH_AES_128_CBC_SHA:
      return "TLS_DH_anon_WITH_AES_128_CBC_SHA";
      break;
    case TLS_RSA_WITH_AES_256_CBC_SHA:
      return "TLS_RSA_WITH_AES_256_CBC_SHA";
      break;
    case TLS_DH_DSS_WITH_AES_256_CBC_SHA:
      return "TLS_DH_DSS_WITH_AES_256_CBC_SHA";
      break;
    case TLS_DH_RSA_WITH_AES_256_CBC_SHA:
      return "TLS_DH_RSA_WITH_AES_256_CBC_SHA";
      break;
    case TLS_DHE_DSS_WITH_AES_256_CBC_SHA:
      return "TLS_DHE_DSS_WITH_AES_256_CBC_SHA";
      break;
    case TLS_DHE_RSA_WITH_AES_256_CBC_SHA:
      return "TLS_DHE_RSA_WITH_AES_256_CBC_SHA";
      break;
    case TLS_DH_anon_WITH_AES_256_CBC_SHA:
      return "TLS_DH_anon_WITH_AES_256_CBC_SHA";
      break;
#if CURL_BUILD_MAC_10_6 || CURL_BUILD_IOS
    /* TLS 1.0 with ECDSA (RFC 4492) */
    case TLS_ECDH_ECDSA_WITH_NULL_SHA:
      return "TLS_ECDH_ECDSA_WITH_NULL_SHA";
      break;
    case TLS_ECDH_ECDSA_WITH_RC4_128_SHA:
      return "TLS_ECDH_ECDSA_WITH_RC4_128_SHA";
      break;
    case TLS_ECDH_ECDSA_WITH_3DES_EDE_CBC_SHA:
      return "TLS_ECDH_ECDSA_WITH_3DES_EDE_CBC_SHA";
      break;
    case TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA:
      return "TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA";
      break;
    case TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA:
      return "TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA";
      break;
    case TLS_ECDHE_ECDSA_WITH_NULL_SHA:
      return "TLS_ECDHE_ECDSA_WITH_NULL_SHA";
      break;
    case TLS_ECDHE_ECDSA_WITH_RC4_128_SHA:
      return "TLS_ECDHE_ECDSA_WITH_RC4_128_SHA";
      break;
    case TLS_ECDHE_ECDSA_WITH_3DES_EDE_CBC_SHA:
      return "TLS_ECDHE_ECDSA_WITH_3DES_EDE_CBC_SHA";
      break;
    case TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA:
      return "TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA";
      break;
    case TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA:
      return "TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA";
      break;
    case TLS_ECDH_RSA_WITH_NULL_SHA:
      return "TLS_ECDH_RSA_WITH_NULL_SHA";
      break;
    case TLS_ECDH_RSA_WITH_RC4_128_SHA:
      return "TLS_ECDH_RSA_WITH_RC4_128_SHA";
      break;
    case TLS_ECDH_RSA_WITH_3DES_EDE_CBC_SHA:
      return "TLS_ECDH_RSA_WITH_3DES_EDE_CBC_SHA";
      break;
    case TLS_ECDH_RSA_WITH_AES_128_CBC_SHA:
      return "TLS_ECDH_RSA_WITH_AES_128_CBC_SHA";
      break;
    case TLS_ECDH_RSA_WITH_AES_256_CBC_SHA:
      return "TLS_ECDH_RSA_WITH_AES_256_CBC_SHA";
      break;
    case TLS_ECDHE_RSA_WITH_NULL_SHA:
      return "TLS_ECDHE_RSA_WITH_NULL_SHA";
      break;
    case TLS_ECDHE_RSA_WITH_RC4_128_SHA:
      return "TLS_ECDHE_RSA_WITH_RC4_128_SHA";
      break;
    case TLS_ECDHE_RSA_WITH_3DES_EDE_CBC_SHA:
      return "TLS_ECDHE_RSA_WITH_3DES_EDE_CBC_SHA";
      break;
    case TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA:
      return "TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA";
      break;
    case TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA:
      return "TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA";
      break;
    case TLS_ECDH_anon_WITH_NULL_SHA:
      return "TLS_ECDH_anon_WITH_NULL_SHA";
      break;
    case TLS_ECDH_anon_WITH_RC4_128_SHA:
      return "TLS_ECDH_anon_WITH_RC4_128_SHA";
      break;
    case TLS_ECDH_anon_WITH_3DES_EDE_CBC_SHA:
      return "TLS_ECDH_anon_WITH_3DES_EDE_CBC_SHA";
      break;
    case TLS_ECDH_anon_WITH_AES_128_CBC_SHA:
      return "TLS_ECDH_anon_WITH_AES_128_CBC_SHA";
      break;
    case TLS_ECDH_anon_WITH_AES_256_CBC_SHA:
      return "TLS_ECDH_anon_WITH_AES_256_CBC_SHA";
      break;
#endif /* CURL_BUILD_MAC_10_6 || CURL_BUILD_IOS */
#if CURL_BUILD_MAC_10_8 || CURL_BUILD_IOS
    /* TLS 1.2 (RFC 5246) */
    case TLS_RSA_WITH_NULL_MD5:
      return "TLS_RSA_WITH_NULL_MD5";
      break;
    case TLS_RSA_WITH_NULL_SHA:
      return "TLS_RSA_WITH_NULL_SHA";
      break;
    case TLS_RSA_WITH_RC4_128_MD5:
      return "TLS_RSA_WITH_RC4_128_MD5";
      break;
    case TLS_RSA_WITH_RC4_128_SHA:
      return "TLS_RSA_WITH_RC4_128_SHA";
      break;
    case TLS_RSA_WITH_3DES_EDE_CBC_SHA:
      return "TLS_RSA_WITH_3DES_EDE_CBC_SHA";
      break;
    case TLS_RSA_WITH_NULL_SHA256:
      return "TLS_RSA_WITH_NULL_SHA256";
      break;
    case TLS_RSA_WITH_AES_128_CBC_SHA256:
      return "TLS_RSA_WITH_AES_128_CBC_SHA256";
      break;
    case TLS_RSA_WITH_AES_256_CBC_SHA256:
      return "TLS_RSA_WITH_AES_256_CBC_SHA256";
      break;
    case TLS_DH_DSS_WITH_3DES_EDE_CBC_SHA:
      return "TLS_DH_DSS_WITH_3DES_EDE_CBC_SHA";
      break;
    case TLS_DH_RSA_WITH_3DES_EDE_CBC_SHA:
      return "TLS_DH_RSA_WITH_3DES_EDE_CBC_SHA";
      break;
    case TLS_DHE_DSS_WITH_3DES_EDE_CBC_SHA:
      return "TLS_DHE_DSS_WITH_3DES_EDE_CBC_SHA";
      break;
    case TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA:
      return "TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA";
      break;
    case TLS_DH_DSS_WITH_AES_128_CBC_SHA256:
      return "TLS_DH_DSS_WITH_AES_128_CBC_SHA256";
      break;
    case TLS_DH_RSA_WITH_AES_128_CBC_SHA256:
      return "TLS_DH_RSA_WITH_AES_128_CBC_SHA256";
      break;
    case TLS_DHE_DSS_WITH_AES_128_CBC_SHA256:
      return "TLS_DHE_DSS_WITH_AES_128_CBC_SHA256";
      break;
    case TLS_DHE_RSA_WITH_AES_128_CBC_SHA256:
      return "TLS_DHE_RSA_WITH_AES_128_CBC_SHA256";
      break;
    case TLS_DH_DSS_WITH_AES_256_CBC_SHA256:
      return "TLS_DH_DSS_WITH_AES_256_CBC_SHA256";
      break;
    case TLS_DH_RSA_WITH_AES_256_CBC_SHA256:
      return "TLS_DH_RSA_WITH_AES_256_CBC_SHA256";
      break;
    case TLS_DHE_DSS_WITH_AES_256_CBC_SHA256:
      return "TLS_DHE_DSS_WITH_AES_256_CBC_SHA256";
      break;
    case TLS_DHE_RSA_WITH_AES_256_CBC_SHA256:
      return "TLS_DHE_RSA_WITH_AES_256_CBC_SHA256";
      break;
    case TLS_DH_anon_WITH_RC4_128_MD5:
      return "TLS_DH_anon_WITH_RC4_128_MD5";
      break;
    case TLS_DH_anon_WITH_3DES_EDE_CBC_SHA:
      return "TLS_DH_anon_WITH_3DES_EDE_CBC_SHA";
      break;
    case TLS_DH_anon_WITH_AES_128_CBC_SHA256:
      return "TLS_DH_anon_WITH_AES_128_CBC_SHA256";
      break;
    case TLS_DH_anon_WITH_AES_256_CBC_SHA256:
      return "TLS_DH_anon_WITH_AES_256_CBC_SHA256";
      break;
    /* TLS 1.2 with AES GCM (RFC 5288) */
    case TLS_RSA_WITH_AES_128_GCM_SHA256:
      return "TLS_RSA_WITH_AES_128_GCM_SHA256";
      break;
    case TLS_RSA_WITH_AES_256_GCM_SHA384:
      return "TLS_RSA_WITH_AES_256_GCM_SHA384";
      break;
    case TLS_DHE_RSA_WITH_AES_128_GCM_SHA256:
      return "TLS_DHE_RSA_WITH_AES_128_GCM_SHA256";
      break;
    case TLS_DHE_RSA_WITH_AES_256_GCM_SHA384:
      return "TLS_DHE_RSA_WITH_AES_256_GCM_SHA384";
      break;
    case TLS_DH_RSA_WITH_AES_128_GCM_SHA256:
      return "TLS_DH_RSA_WITH_AES_128_GCM_SHA256";
      break;
    case TLS_DH_RSA_WITH_AES_256_GCM_SHA384:
      return "TLS_DH_RSA_WITH_AES_256_GCM_SHA384";
      break;
    case TLS_DHE_DSS_WITH_AES_128_GCM_SHA256:
      return "TLS_DHE_DSS_WITH_AES_128_GCM_SHA256";
      break;
    case TLS_DHE_DSS_WITH_AES_256_GCM_SHA384:
      return "TLS_DHE_DSS_WITH_AES_256_GCM_SHA384";
      break;
    case TLS_DH_DSS_WITH_AES_128_GCM_SHA256:
      return "TLS_DH_DSS_WITH_AES_128_GCM_SHA256";
      break;
    case TLS_DH_DSS_WITH_AES_256_GCM_SHA384:
      return "TLS_DH_DSS_WITH_AES_256_GCM_SHA384";
      break;
    case TLS_DH_anon_WITH_AES_128_GCM_SHA256:
      return "TLS_DH_anon_WITH_AES_128_GCM_SHA256";
      break;
    case TLS_DH_anon_WITH_AES_256_GCM_SHA384:
      return "TLS_DH_anon_WITH_AES_256_GCM_SHA384";
      break;
    /* TLS 1.2 with elliptic curve ciphers (RFC 5289) */
    case TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256:
      return "TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256";
      break;
    case TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA384:
      return "TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA384";
      break;
    case TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA256:
      return "TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA256";
      break;
    case TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA384:
      return "TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA384";
      break;
    case TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256:
      return "TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256";
      break;
    case TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384:
      return "TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384";
      break;
    case TLS_ECDH_RSA_WITH_AES_128_CBC_SHA256:
      return "TLS_ECDH_RSA_WITH_AES_128_CBC_SHA256";
      break;
    case TLS_ECDH_RSA_WITH_AES_256_CBC_SHA384:
      return "TLS_ECDH_RSA_WITH_AES_256_CBC_SHA384";
      break;
    case TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256:
      return "TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256";
      break;
    case TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384:
      return "TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384";
      break;
    case TLS_ECDH_ECDSA_WITH_AES_128_GCM_SHA256:
      return "TLS_ECDH_ECDSA_WITH_AES_128_GCM_SHA256";
      break;
    case TLS_ECDH_ECDSA_WITH_AES_256_GCM_SHA384:
      return "TLS_ECDH_ECDSA_WITH_AES_256_GCM_SHA384";
      break;
    case TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256:
      return "TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256";
      break;
    case TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384:
      return "TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384";
      break;
    case TLS_ECDH_RSA_WITH_AES_128_GCM_SHA256:
      return "TLS_ECDH_RSA_WITH_AES_128_GCM_SHA256";
      break;
    case TLS_ECDH_RSA_WITH_AES_256_GCM_SHA384:
      return "TLS_ECDH_RSA_WITH_AES_256_GCM_SHA384";
      break;
    case TLS_EMPTY_RENEGOTIATION_INFO_SCSV:
      return "TLS_EMPTY_RENEGOTIATION_INFO_SCSV";
      break;
#else
    case SSL_RSA_WITH_NULL_MD5:
      return "TLS_RSA_WITH_NULL_MD5";
      break;
    case SSL_RSA_WITH_NULL_SHA:
      return "TLS_RSA_WITH_NULL_SHA";
      break;
    case SSL_RSA_WITH_RC4_128_MD5:
      return "TLS_RSA_WITH_RC4_128_MD5";
      break;
    case SSL_RSA_WITH_RC4_128_SHA:
      return "TLS_RSA_WITH_RC4_128_SHA";
      break;
    case SSL_RSA_WITH_3DES_EDE_CBC_SHA:
      return "TLS_RSA_WITH_3DES_EDE_CBC_SHA";
      break;
    case SSL_DH_anon_WITH_RC4_128_MD5:
      return "TLS_DH_anon_WITH_RC4_128_MD5";
      break;
    case SSL_DH_anon_WITH_3DES_EDE_CBC_SHA:
      return "TLS_DH_anon_WITH_3DES_EDE_CBC_SHA";
      break;
#endif /* CURL_BUILD_MAC_10_8 || CURL_BUILD_IOS */
#if CURL_BUILD_MAC_10_9 || CURL_BUILD_IOS_7
    /* TLS PSK (RFC 4279): */
    case TLS_PSK_WITH_RC4_128_SHA:
      return "TLS_PSK_WITH_RC4_128_SHA";
      break;
    case TLS_PSK_WITH_3DES_EDE_CBC_SHA:
      return "TLS_PSK_WITH_3DES_EDE_CBC_SHA";
      break;
    case TLS_PSK_WITH_AES_128_CBC_SHA:
      return "TLS_PSK_WITH_AES_128_CBC_SHA";
      break;
    case TLS_PSK_WITH_AES_256_CBC_SHA:
      return "TLS_PSK_WITH_AES_256_CBC_SHA";
      break;
    case TLS_DHE_PSK_WITH_RC4_128_SHA:
      return "TLS_DHE_PSK_WITH_RC4_128_SHA";
      break;
    case TLS_DHE_PSK_WITH_3DES_EDE_CBC_SHA:
      return "TLS_DHE_PSK_WITH_3DES_EDE_CBC_SHA";
      break;
    case TLS_DHE_PSK_WITH_AES_128_CBC_SHA:
      return "TLS_DHE_PSK_WITH_AES_128_CBC_SHA";
      break;
    case TLS_DHE_PSK_WITH_AES_256_CBC_SHA:
      return "TLS_DHE_PSK_WITH_AES_256_CBC_SHA";
      break;
    case TLS_RSA_PSK_WITH_RC4_128_SHA:
      return "TLS_RSA_PSK_WITH_RC4_128_SHA";
      break;
    case TLS_RSA_PSK_WITH_3DES_EDE_CBC_SHA:
      return "TLS_RSA_PSK_WITH_3DES_EDE_CBC_SHA";
      break;
    case TLS_RSA_PSK_WITH_AES_128_CBC_SHA:
      return "TLS_RSA_PSK_WITH_AES_128_CBC_SHA";
      break;
    case TLS_RSA_PSK_WITH_AES_256_CBC_SHA:
      return "TLS_RSA_PSK_WITH_AES_256_CBC_SHA";
      break;
    /* More TLS PSK (RFC 4785): */
    case TLS_PSK_WITH_NULL_SHA:
      return "TLS_PSK_WITH_NULL_SHA";
      break;
    case TLS_DHE_PSK_WITH_NULL_SHA:
      return "TLS_DHE_PSK_WITH_NULL_SHA";
      break;
    case TLS_RSA_PSK_WITH_NULL_SHA:
      return "TLS_RSA_PSK_WITH_NULL_SHA";
      break;
    /* Even more TLS PSK (RFC 5487): */
    case TLS_PSK_WITH_AES_128_GCM_SHA256:
      return "TLS_PSK_WITH_AES_128_GCM_SHA256";
      break;
    case TLS_PSK_WITH_AES_256_GCM_SHA384:
      return "TLS_PSK_WITH_AES_256_GCM_SHA384";
      break;
    case TLS_DHE_PSK_WITH_AES_128_GCM_SHA256:
      return "TLS_DHE_PSK_WITH_AES_128_GCM_SHA256";
      break;
    case TLS_DHE_PSK_WITH_AES_256_GCM_SHA384:
      return "TLS_DHE_PSK_WITH_AES_256_GCM_SHA384";
      break;
    case TLS_RSA_PSK_WITH_AES_128_GCM_SHA256:
      return "TLS_RSA_PSK_WITH_AES_128_GCM_SHA256";
      break;
    case TLS_RSA_PSK_WITH_AES_256_GCM_SHA384:
      return "TLS_PSK_WITH_AES_256_GCM_SHA384";
      break;
    case TLS_PSK_WITH_AES_128_CBC_SHA256:
      return "TLS_PSK_WITH_AES_128_CBC_SHA256";
      break;
    case TLS_PSK_WITH_AES_256_CBC_SHA384:
      return "TLS_PSK_WITH_AES_256_CBC_SHA384";
      break;
    case TLS_PSK_WITH_NULL_SHA256:
      return "TLS_PSK_WITH_NULL_SHA256";
      break;
    case TLS_PSK_WITH_NULL_SHA384:
      return "TLS_PSK_WITH_NULL_SHA384";
      break;
    case TLS_DHE_PSK_WITH_AES_128_CBC_SHA256:
      return "TLS_DHE_PSK_WITH_AES_128_CBC_SHA256";
      break;
    case TLS_DHE_PSK_WITH_AES_256_CBC_SHA384:
      return "TLS_DHE_PSK_WITH_AES_256_CBC_SHA384";
      break;
    case TLS_DHE_PSK_WITH_NULL_SHA256:
      return "TLS_DHE_PSK_WITH_NULL_SHA256";
      break;
    case TLS_DHE_PSK_WITH_NULL_SHA384:
      return "TLS_RSA_PSK_WITH_NULL_SHA384";
      break;
    case TLS_RSA_PSK_WITH_AES_128_CBC_SHA256:
      return "TLS_RSA_PSK_WITH_AES_128_CBC_SHA256";
      break;
    case TLS_RSA_PSK_WITH_AES_256_CBC_SHA384:
      return "TLS_RSA_PSK_WITH_AES_256_CBC_SHA384";
      break;
    case TLS_RSA_PSK_WITH_NULL_SHA256:
      return "TLS_RSA_PSK_WITH_NULL_SHA256";
      break;
    case TLS_RSA_PSK_WITH_NULL_SHA384:
      return "TLS_RSA_PSK_WITH_NULL_SHA384";
      break;
#endif /* CURL_BUILD_MAC_10_9 || CURL_BUILD_IOS_7 */
  }