{
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