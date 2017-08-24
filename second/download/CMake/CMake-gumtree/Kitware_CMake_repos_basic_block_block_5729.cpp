{
        tmplen = (strlen(v->data) + 1);
        /* Add the variable only if it fits */
        if(len + tmplen < (int)sizeof(temp)-6) {
          if(sscanf(v->data, "%127[^,],%127s", varname, varval)) {
            snprintf((char *)&temp[len], sizeof(temp) - len,
                     "%c%s%c%s", CURL_NEW_ENV_VAR, varname,
                     CURL_NEW_ENV_VALUE, varval);
            len += tmplen;
          }
        }
      }