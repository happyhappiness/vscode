{
        /* Disable NULL ciphersuites: */
        case SSL_NULL_WITH_NULL_NULL:
        case SSL_RSA_WITH_NULL_MD5:
        case SSL_RSA_WITH_NULL_SHA:
        case 0x003B: /* TLS_RSA_WITH_NULL_SHA256 */
        case SSL_FORTEZZA_DMS_WITH_NULL_SHA:
        case 0xC001: /* TLS_ECDH_ECDSA_WITH_NULL_SHA */
        case 0xC006: /* TLS_ECDHE_ECDSA_WITH_NULL_SHA */
        case 0xC00B: /* TLS_ECDH_RSA_WITH_NULL_SHA */
        case 0xC010: /* TLS_ECDHE_RSA_WITH_NULL_SHA */
        case 0x002C: /* TLS_PSK_WITH_NULL_SHA */
        case 0x002D: /* TLS_DHE_PSK_WITH_NULL_SHA */
        case 0x002E: /* TLS_RSA_PSK_WITH_NULL_SHA */
        case 0x00B0: /* TLS_PSK_WITH_NULL_SHA256 */
        case 0x00B1: /* TLS_PSK_WITH_NULL_SHA384 */
        case 0x00B4: /* TLS_DHE_PSK_WITH_NULL_SHA256 */
        case 0x00B5: /* TLS_DHE_PSK_WITH_NULL_SHA384 */
        case 0x00B8: /* TLS_RSA_PSK_WITH_NULL_SHA256 */
        case 0x00B9: /* TLS_RSA_PSK_WITH_NULL_SHA384 */
        /* Disable anonymous ciphersuites: */
        case SSL_DH_anon_EXPORT_WITH_RC4_40_MD5:
        case SSL_DH_anon_WITH_RC4_128_MD5:
        case SSL_DH_anon_EXPORT_WITH_DES40_CBC_SHA:
        case SSL_DH_anon_WITH_DES_CBC_SHA:
        case SSL_DH_anon_WITH_3DES_EDE_CBC_SHA:
        case TLS_DH_anon_WITH_AES_128_CBC_SHA:
        case TLS_DH_anon_WITH_AES_256_CBC_SHA:
        case 0xC015: /* TLS_ECDH_anon_WITH_NULL_SHA */
        case 0xC016: /* TLS_ECDH_anon_WITH_RC4_128_SHA */
        case 0xC017: /* TLS_ECDH_anon_WITH_3DES_EDE_CBC_SHA */
        case 0xC018: /* TLS_ECDH_anon_WITH_AES_128_CBC_SHA */
        case 0xC019: /* TLS_ECDH_anon_WITH_AES_256_CBC_SHA */
        case 0x006C: /* TLS_DH_anon_WITH_AES_128_CBC_SHA256 */
        case 0x006D: /* TLS_DH_anon_WITH_AES_256_CBC_SHA256 */
        case 0x00A6: /* TLS_DH_anon_WITH_AES_128_GCM_SHA256 */
        case 0x00A7: /* TLS_DH_anon_WITH_AES_256_GCM_SHA384 */
        /* Disable weak key ciphersuites: */
        case SSL_RSA_EXPORT_WITH_RC4_40_MD5:
        case SSL_RSA_EXPORT_WITH_RC2_CBC_40_MD5:
        case SSL_RSA_EXPORT_WITH_DES40_CBC_SHA:
        case SSL_DH_DSS_EXPORT_WITH_DES40_CBC_SHA:
        case SSL_DH_RSA_EXPORT_WITH_DES40_CBC_SHA:
        case SSL_DHE_DSS_EXPORT_WITH_DES40_CBC_SHA:
        case SSL_DHE_RSA_EXPORT_WITH_DES40_CBC_SHA:
        case SSL_RSA_WITH_DES_CBC_SHA:
        case SSL_DH_DSS_WITH_DES_CBC_SHA:
        case SSL_DH_RSA_WITH_DES_CBC_SHA:
        case SSL_DHE_DSS_WITH_DES_CBC_SHA:
        case SSL_DHE_RSA_WITH_DES_CBC_SHA:
        /* Disable IDEA: */
        case SSL_RSA_WITH_IDEA_CBC_SHA:
        case SSL_RSA_WITH_IDEA_CBC_MD5:
        /* Disable RC4: */
        case SSL_RSA_WITH_RC4_128_MD5:
        case SSL_RSA_WITH_RC4_128_SHA:
        case 0xC002: /* TLS_ECDH_ECDSA_WITH_RC4_128_SHA */
        case 0xC007: /* TLS_ECDHE_ECDSA_WITH_RC4_128_SHA*/
        case 0xC00C: /* TLS_ECDH_RSA_WITH_RC4_128_SHA */
        case 0xC011: /* TLS_ECDHE_RSA_WITH_RC4_128_SHA */
        case 0x008A: /* TLS_PSK_WITH_RC4_128_SHA */
        case 0x008E: /* TLS_DHE_PSK_WITH_RC4_128_SHA */
        case 0x0092: /* TLS_RSA_PSK_WITH_RC4_128_SHA */
          break;
        default: /* enable everything else */
          allowed_ciphers[allowed_ciphers_count++] = all_ciphers[i];
          break;
      }