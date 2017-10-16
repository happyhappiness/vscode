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
