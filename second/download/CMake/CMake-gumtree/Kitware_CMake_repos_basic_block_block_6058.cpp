{
    strncpy(proxypasswd, data->set.str[STRING_PROXYPASSWORD],
            MAX_CURL_PASSWORD_LENGTH);
    proxypasswd[MAX_CURL_PASSWORD_LENGTH-1] = '\0'; /*To be on safe side*/
  }