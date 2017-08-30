  }

  snprintf(data->state.buffer, sizeof(data->state.buffer), "%s:%s", user, pwd);
  if(Curl_base64_encode(data, data->state.buffer,
                        strlen(data->state.buffer),
                        &authorization) > 0) {
    if(*userp)
      free(*userp);
    *userp = aprintf( "%sAuthorization: Basic %s\r\n",
                      proxy?"Proxy-":"",
                      authorization);
    free(authorization);
