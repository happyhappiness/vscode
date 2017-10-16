          warnf(config, "--metalink option is ignored because the binary is "
                "built without the Metalink support.\n");
#endif
          break;
        }
      case 'K': /* --sasl-ir */
        config->sasl_ir = TRUE;
        break;
      }
      break;
    case '#': /* --progress-bar */
      if(toggle)
        config->progressmode = CURL_PROGRESS_BAR;
      else
        config->progressmode = CURL_PROGRESS_STATS;
      break;
    case '~': /* --xattr */
      config->xattr = toggle;
      break;
    case '0':
      /* HTTP version 1.0 */
      config->httpversion = CURL_HTTP_VERSION_1_0;
      break;
    case '1':
      /* TLS version 1 */
      config->ssl_version = CURL_SSLVERSION_TLSv1;
      break;
    case '2':
