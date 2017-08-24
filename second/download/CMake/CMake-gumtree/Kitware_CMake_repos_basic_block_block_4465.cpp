{
          Curl_infof(data, "base64-encoding: %s\n",
                     curl_easy_strerror(result));
          ret = AUTH_ERROR;
          break;
        }