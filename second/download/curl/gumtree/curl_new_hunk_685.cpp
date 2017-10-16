      case 'G': /* --delegation LEVEL */
        config->gssapi_delegation = delegation(config, nextarg);
        break;
      case 'H': /* --mail-auth */
        GetStr(&config->mail_auth, nextarg);
        break;
      case 'J': /* --metalink */
        {
#ifdef USE_METALINK
          int mlmaj, mlmin, mlpatch;
          metalink_get_version(&mlmaj, &mlmin, &mlpatch);
          if((mlmaj*10000)+(mlmin*100)+mlpatch < CURL_REQ_LIBMETALINK_VERS) {
            warnf(config,
                  "--metalink option cannot be used because the version of "
                  "the linked libmetalink library is too old. "
                  "Required: %d.%d.%d, found %d.%d.%d\n",
                  CURL_REQ_LIBMETALINK_MAJOR,
                  CURL_REQ_LIBMETALINK_MINOR,
                  CURL_REQ_LIBMETALINK_PATCH,
                  mlmaj, mlmin, mlpatch);
            return PARAM_BAD_USE;
          }
          else
            config->use_metalink = toggle;
#else
          warnf(config, "--metalink option is ignored because the binary is "
                "built without the Metalink support.\n");
#endif
          break;
        }
      }
      break;
    case '#': /* --progress-bar */
      if(toggle)
        config->progressmode = CURL_PROGRESS_BAR;
      else
