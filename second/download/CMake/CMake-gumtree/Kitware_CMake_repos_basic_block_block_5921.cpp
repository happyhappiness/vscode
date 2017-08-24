f(canpipe) {
      if(bundle->multiuse <= BUNDLE_UNKNOWN) {
        if((bundle->multiuse == BUNDLE_UNKNOWN) && data->set.pipewait) {
          infof(data, "Server doesn't support multi-use yet, wait\n");
          *waitpipe = TRUE;
          return FALSE; /* no re-use */
        }

        infof(data, "Server doesn't support multi-use (yet)\n");
        canpipe = 0;
      }
      if((bundle->multiuse == BUNDLE_PIPELINING) &&
         !Curl_pipeline_wanted(data->multi, CURLPIPE_HTTP1)) {
        /* not asked for, switch off */
        infof(data, "Could pipeline, but not asked to!\n");
        canpipe = 0;
      }
      else if((bundle->multiuse == BUNDLE_MULTIPLEX) &&
              !Curl_pipeline_wanted(data->multi, CURLPIPE_MULTIPLEX)) {
        infof(data, "Could multiplex, but not asked to!\n");
        canpipe = 0;
      }
    }