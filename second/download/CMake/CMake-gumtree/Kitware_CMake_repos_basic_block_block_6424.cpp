{
    /* SSL version 3.0 */
    case SSL_RSA_WITH_NULL_MD5:
      return "SSL_RSA_WITH_NULL_MD5";
      break;
    case SSL_RSA_WITH_NULL_SHA:
      return "SSL_RSA_WITH_NULL_SHA";
      break;
    case SSL_RSA_EXPORT_WITH_RC4_40_MD5:
      return "SSL_RSA_EXPORT_WITH_RC4_40_MD5";
      break;
    case SSL_RSA_WITH_RC4_128_MD5:
      return "SSL_RSA_WITH_RC4_128_MD5";
      break;
    case SSL_RSA_WITH_RC4_128_SHA:
      return "SSL_RSA_WITH_RC4_128_SHA";
      break;
    case SSL_RSA_EXPORT_WITH_RC2_CBC_40_MD5:
      return "SSL_RSA_EXPORT_WITH_RC2_CBC_40_MD5";
      break;
    case SSL_RSA_WITH_IDEA_CBC_SHA:
      return "SSL_RSA_WITH_IDEA_CBC_SHA";
      break;
    case SSL_RSA_EXPORT_WITH_DES40_CBC_SHA:
      return "SSL_RSA_EXPORT_WITH_DES40_CBC_SHA";
      break;
    case SSL_RSA_WITH_DES_CBC_SHA:
      return "SSL_RSA_WITH_DES_CBC_SHA";
      break;
    case SSL_RSA_WITH_3DES_EDE_CBC_SHA:
      return "SSL_RSA_WITH_3DES_EDE_CBC_SHA";
      break;
    case SSL_DH_DSS_EXPORT_WITH_DES40_CBC_SHA:
      return "SSL_DH_DSS_EXPORT_WITH_DES40_CBC_SHA";
      break;
    case SSL_DH_DSS_WITH_DES_CBC_SHA:
      return "SSL_DH_DSS_WITH_DES_CBC_SHA";
      break;
    case SSL_DH_DSS_WITH_3DES_EDE_CBC_SHA:
      return "SSL_DH_DSS_WITH_3DES_EDE_CBC_SHA";
      break;
    case SSL_DH_RSA_EXPORT_WITH_DES40_CBC_SHA:
      return "SSL_DH_RSA_EXPORT_WITH_DES40_CBC_SHA";
      break;
    case SSL_DH_RSA_WITH_DES_CBC_SHA:
      return "SSL_DH_RSA_WITH_DES_CBC_SHA";
      break;
    case SSL_DH_RSA_WITH_3DES_EDE_CBC_SHA:
      return "SSL_DH_RSA_WITH_3DES_EDE_CBC_SHA";
      break;
    case SSL_DHE_DSS_EXPORT_WITH_DES40_CBC_SHA:
      return "SSL_DHE_DSS_EXPORT_WITH_DES40_CBC_SHA";
      break;
    case SSL_DHE_DSS_WITH_DES_CBC_SHA:
      return "SSL_DHE_DSS_WITH_DES_CBC_SHA";
      break;
    case SSL_DHE_DSS_WITH_3DES_EDE_CBC_SHA:
      return "SSL_DHE_DSS_WITH_3DES_EDE_CBC_SHA";
      break;
    case SSL_DHE_RSA_EXPORT_WITH_DES40_CBC_SHA:
      return "SSL_DHE_RSA_EXPORT_WITH_DES40_CBC_SHA";
      break;
    case SSL_DHE_RSA_WITH_DES_CBC_SHA:
      return "SSL_DHE_RSA_WITH_DES_CBC_SHA";
      break;
    case SSL_DHE_RSA_WITH_3DES_EDE_CBC_SHA:
      return "SSL_DHE_RSA_WITH_3DES_EDE_CBC_SHA";
      break;
    case SSL_DH_anon_EXPORT_WITH_RC4_40_MD5:
      return "SSL_DH_anon_EXPORT_WITH_RC4_40_MD5";
      break;
    case SSL_DH_anon_WITH_RC4_128_MD5:
      return "SSL_DH_anon_WITH_RC4_128_MD5";
      break;
    case SSL_DH_anon_EXPORT_WITH_DES40_CBC_SHA:
      return "SSL_DH_anon_EXPORT_WITH_DES40_CBC_SHA";
      break;
    case SSL_DH_anon_WITH_DES_CBC_SHA:
      return "SSL_DH_anon_WITH_DES_CBC_SHA";
      break;
    case SSL_DH_anon_WITH_3DES_EDE_CBC_SHA:
      return "SSL_DH_anon_WITH_3DES_EDE_CBC_SHA";
      break;
    case SSL_FORTEZZA_DMS_WITH_NULL_SHA:
      return "SSL_FORTEZZA_DMS_WITH_NULL_SHA";
      break;
    case SSL_FORTEZZA_DMS_WITH_FORTEZZA_CBC_SHA:
      return "SSL_FORTEZZA_DMS_WITH_FORTEZZA_CBC_SHA";
      break;
    /* TLS 1.0 with AES (RFC 3268)
       (Apparently these are used in SSLv3 implementations as well.) */
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
    /* SSL version 2.0 */
    case SSL_RSA_WITH_RC2_CBC_MD5:
      return "SSL_RSA_WITH_RC2_CBC_MD5";
      break;
    case SSL_RSA_WITH_IDEA_CBC_MD5:
      return "SSL_RSA_WITH_IDEA_CBC_MD5";
      break;
    case SSL_RSA_WITH_DES_CBC_MD5:
      return "SSL_RSA_WITH_DES_CBC_MD5";
      break;
    case SSL_RSA_WITH_3DES_EDE_CBC_MD5:
      return "SSL_RSA_WITH_3DES_EDE_CBC_MD5";
      break;
  }