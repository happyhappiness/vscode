
  snprintf(data->state.buffer, sizeof(data->state.buffer), "%s:%s", user, pwd);

  error = Curl_base64_encode(data,
                             data->state.buffer, strlen(data->state.buffer),
                             &authorization, &size);
  if(error)
    return error;

  if(!authorization)
    return CURLE_REMOTE_ACCESS_DENIED;

  Curl_safefree(*userp);
  *userp = aprintf("%sAuthorization: Basic %s\r\n",
                   proxy?"Proxy-":"",
                   authorization);
