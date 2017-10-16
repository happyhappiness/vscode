        break;
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
