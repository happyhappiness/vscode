    pwd = conn->passwd;

  }



  snprintf(data->state.buffer, CURL_BUFSIZE(data->set.buffer_size),

           "%s:%s", user, pwd);



  result = Curl_base64_encode(data,

                              data->state.buffer, strlen(data->state.buffer),

