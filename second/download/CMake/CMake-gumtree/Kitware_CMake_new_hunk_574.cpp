
  snprintf(data->state.buffer, sizeof(data->state.buffer), "%s:%s", user, pwd);

  result = Curl_base64_encode(data,
                              data->state.buffer, strlen(data->state.buffer),
                              &authorization, &size);
  if(result)
    return result;

  if(!authorization)
    return CURLE_REMOTE_ACCESS_DENIED;

  free(*userp);
  *userp = aprintf("%sAuthorization: Basic %s\r\n",
                   proxy?"Proxy-":"",
                   authorization);
