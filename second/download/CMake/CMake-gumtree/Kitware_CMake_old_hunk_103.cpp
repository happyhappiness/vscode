    pwd = conn->passwd;
  }

  snprintf(data->state.buffer, sizeof(data->state.buffer), "%s:%s", user, pwd);

  result = Curl_base64_encode(data,
                              data->state.buffer, strlen(data->state.buffer),
