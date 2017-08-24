{
        beg = curl_slist_append(tn->telnet_vars, option_arg);
        if(!beg) {
          result = CURLE_OUT_OF_MEMORY;
          break;
        }
        tn->telnet_vars = beg;
        tn->us_preferred[CURL_TELOPT_NEW_ENVIRON] = CURL_YES;
        continue;
      }