      case 'J': /* --metalink */
        {
#ifdef USE_METALINK
          int mlmaj, mlmin, mlpatch;
          metalink_get_version(&mlmaj, &mlmin, &mlpatch);
          if((mlmaj*10000)+(mlmin*100)+mlpatch < CURL_REQ_LIBMETALINK_VERS) {
            warnf(global,
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
          warnf(global, "--metalink option is ignored because the binary is "
                "built without the Metalink support.\n");
#endif
          break;
        }
      case 'K': /* --sasl-ir */
        config->sasl_ir = toggle;
        break;
      case 'L': /* --test-event */
#ifdef CURLDEBUG
        config->test_event_based = toggle;
#else
        warnf(global, "--test-event is ignored unless a debug build!\n");
#endif
        break;
      case 'M': /* --unix-socket */
        GetStr(&config->unix_socket_path, nextarg);
        break;
      case 'N': /* --path-as-is */
        config->path_as_is = toggle;
        break;
      }
      break;
    case '#': /* --progress-bar */
      if(toggle)
        global->progressmode = CURL_PROGRESS_BAR;
      else
