    pwd = conn->passwd;
  }

  snprintf(data->state.buffer, CURL_BUFSIZE(data->set.buffer_size),
           "%s:%s", user, pwd);

  result = Curl_base64_encode(data,
                              data->state.buffer, strlen(data->state.buffer),
                              &authorization, &size);
  if(result)
    return result;

  if(!authorization)
    return CURLE_REMOTE_ACCESS_DENIED;

  free(*userp);
  *userp = aprintf("%sAuthorization: Basic %s\r\n",
                   proxy ? "Proxy-" : "",
                   authorization);
  free(authorization);
  if(!*userp)
    return CURLE_OUT_OF_MEMORY;

  return CURLE_OK;
}

/* pickoneauth() selects the most favourable authentication method from the
