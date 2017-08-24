f(direction) {
      infof(data, "%s IAC SB ", (direction == '<')? "RCVD":"SENT");
      if(length >= 3) {
        int j;

        i = pointer[length-2];
        j = pointer[length-1];

        if(i != CURL_IAC || j != CURL_SE) {
          infof(data, "(terminated by ");
          if(CURL_TELOPT_OK(i))
            infof(data, "%s ", CURL_TELOPT(i));
          else if(CURL_TELCMD_OK(i))
            infof(data, "%s ", CURL_TELCMD(i));
          else
            infof(data, "%u ", i);
          if(CURL_TELOPT_OK(j))
            infof(data, "%s", CURL_TELOPT(j));
          else if(CURL_TELCMD_OK(j))
            infof(data, "%s", CURL_TELCMD(j));
          else
            infof(data, "%d", j);
          infof(data, ", not IAC SE!) ");
        }
      }
      length -= 2;
    }