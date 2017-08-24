{
      infof(data, "failed to add handle to multi\n");
      http2_stream_free(newhandle->req.protop);
      Curl_close(newhandle);
      rv = 1;
      goto fail;
    }