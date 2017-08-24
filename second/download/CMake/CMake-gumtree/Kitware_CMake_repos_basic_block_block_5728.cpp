f(sscanf(v->data, "%127[^,],%127s", varname, varval)) {
            snprintf((char *)&temp[len], sizeof(temp) - len,
                     "%c%s%c%s", CURL_NEW_ENV_VAR, varname,
                     CURL_NEW_ENV_VALUE, varval);
            len += tmplen;
          }