f(data->state.buffer[0] != '2' && data->state.buffer[0] != '3') {
          Curl_infof(data, "Server didn't accept auth data\n");
          ret = AUTH_ERROR;
          break;
        }