f(Curl_pipeline_wanted(handle->multi, CURLPIPE_HTTP1) &&
       (handle->set.httpversion != CURL_HTTP_VERSION_1_0) &&
       (handle->set.httpreq == HTTPREQ_GET ||
        handle->set.httpreq == HTTPREQ_HEAD))
      /* didn't ask for HTTP/1.0 and a GET or HEAD */
      avail |= CURLPIPE_HTTP1