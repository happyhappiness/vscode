{
      CURLMsg *msg = curl_multi_info_read(multi, &rc);
      if(msg) {
        result = msg->data.result;
        done = TRUE;
      }
    }