#ifdef CURLDEBUG
        config->test_event_based = toggle;
#else
        warnf(config, "--test-event is ignored unless a debug build!\n");
#endif
        break;
      }
      break;
    case '#': /* --progress-bar */
      if(toggle)
        global->progressmode = CURL_PROGRESS_BAR;
      else
