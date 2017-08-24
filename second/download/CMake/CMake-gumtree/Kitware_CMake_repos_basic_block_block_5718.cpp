f(strcasecompare(option_keyword, "BINARY")) {
        binary_option=atoi(option_arg);
        if(binary_option!=1) {
          tn->us_preferred[CURL_TELOPT_BINARY] = CURL_NO;
          tn->him_preferred[CURL_TELOPT_BINARY] = CURL_NO;
        }
        continue;
      }