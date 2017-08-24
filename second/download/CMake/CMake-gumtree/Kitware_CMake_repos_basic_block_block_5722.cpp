{
    if(sscanf(head->data, "%127[^= ]%*[ =]%255s",
              option_keyword, option_arg) == 2) {

      /* Terminal type */
      if(strcasecompare(option_keyword, "TTYPE")) {
        strncpy(tn->subopt_ttype, option_arg, 31);
        tn->subopt_ttype[31] = 0; /* String termination */
        tn->us_preferred[CURL_TELOPT_TTYPE] = CURL_YES;
        continue;
      }

      /* Display variable */
      if(strcasecompare(option_keyword, "XDISPLOC")) {
        strncpy(tn->subopt_xdisploc, option_arg, 127);
        tn->subopt_xdisploc[127] = 0; /* String termination */
        tn->us_preferred[CURL_TELOPT_XDISPLOC] = CURL_YES;
        continue;
      }

      /* Environment variable */
      if(strcasecompare(option_keyword, "NEW_ENV")) {
        beg = curl_slist_append(tn->telnet_vars, option_arg);
        if(!beg) {
          result = CURLE_OUT_OF_MEMORY;
          break;
        }
        tn->telnet_vars = beg;
        tn->us_preferred[CURL_TELOPT_NEW_ENVIRON] = CURL_YES;
        continue;
      }

      /* Window Size */
      if(strcasecompare(option_keyword, "WS")) {
        if(sscanf(option_arg, "%hu%*[xX]%hu",
                  &tn->subopt_wsx, &tn->subopt_wsy) == 2)
          tn->us_preferred[CURL_TELOPT_NAWS] = CURL_YES;
        else {
          failf(data, "Syntax error in telnet option: %s", head->data);
          result = CURLE_TELNET_OPTION_SYNTAX;
          break;
        }
        continue;
      }

      /* To take care or not of the 8th bit in data exchange */
      if(strcasecompare(option_keyword, "BINARY")) {
        binary_option=atoi(option_arg);
        if(binary_option!=1) {
          tn->us_preferred[CURL_TELOPT_BINARY] = CURL_NO;
          tn->him_preferred[CURL_TELOPT_BINARY] = CURL_NO;
        }
        continue;
      }

      failf(data, "Unknown telnet option %s", head->data);
      result = CURLE_UNKNOWN_TELNET_OPTION;
      break;
    }
    failf(data, "Syntax error in telnet option: %s", head->data);
    result = CURLE_TELNET_OPTION_SYNTAX;
    break;
  }