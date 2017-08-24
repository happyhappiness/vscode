{
        infof(data, "schannel: failed to send close msg: %s"
              " (bytes written: %zd)\n", curl_easy_strerror(result), written);
      }