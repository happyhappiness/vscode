multistate(data, Curl_pipeline_wanted(multi, CURLPIPE_HTTP1)?
                       CURLM_STATE_WAITDO:CURLM_STATE_DO)