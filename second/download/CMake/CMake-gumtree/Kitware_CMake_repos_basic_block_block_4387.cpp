{
          /* Send the connect request to the proxy */
          /* BLOCKING */
          result =
            Curl_add_buffer_send(req_buffer, conn,
                                 &data->info.request_size, 0, sockindex);
        }