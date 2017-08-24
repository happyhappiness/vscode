{
      second->req.protop = http;
      http->header_recvbuf = Curl_add_buffer_init();
      if(!http->header_recvbuf) {
        free(http);
        (void)Curl_close(second);
        second = NULL;
      }
      else {
        Curl_http2_setup_req(second);
        second->state.stream_weight = data->state.stream_weight;
      }
    }