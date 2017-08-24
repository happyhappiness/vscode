{
        /* only signal change if the value actually changed */
        infof(conn->data,
              "Connection state changed (MAX_CONCURRENT_STREAMS updated)!\n");
        Curl_multi_connchanged(conn->data->multi);
      }