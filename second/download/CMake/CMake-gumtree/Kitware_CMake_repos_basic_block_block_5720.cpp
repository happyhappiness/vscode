f(strcasecompare(option_keyword, "WS")) {
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