{
      case errSecAuthFailed: case -25264: /* errSecPkcs12VerifyFailure */
        failf(data, "SSL: Incorrect password for the certificate \"%s\" "
                    "and its private key.", ssl_cert);
        break;
      case -26275: /* errSecDecode */ case -25257: /* errSecUnknownFormat */
        failf(data, "SSL: Couldn't make sense of the data in the "
                    "certificate \"%s\" and its private key.",
                    ssl_cert);
        break;
      case -25260: /* errSecPassphraseRequired */
        failf(data, "SSL The certificate \"%s\" requires a password.",
                    ssl_cert);
        break;
      case errSecItemNotFound:
        failf(data, "SSL: Can't find the certificate \"%s\" and its private "
                    "key in the Keychain.", ssl_cert);
        break;
      default:
        failf(data, "SSL: Can't load the certificate \"%s\" and its private "
                    "key: OSStatus %d", ssl_cert, err);
        break;
      }