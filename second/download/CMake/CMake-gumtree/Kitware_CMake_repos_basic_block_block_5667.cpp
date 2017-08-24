f(fmt) {
        if(CURL_TELOPT_OK(option))
          opt = CURL_TELOPT(option);
        else if(option == CURL_TELOPT_EXOPL)
          opt = "EXOPL";
        else
          opt = NULL;

        if(opt)
          infof(data, "%s %s %s\n", direction, fmt, opt);
        else
          infof(data, "%s %s %d\n", direction, fmt, option);
      }
      else
        infof(data, "%s %d %d\n", direction, cmd, option)