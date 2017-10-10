 #ifdef USE_CURL_MULTI
 	CURLMcode curlm_result = curl_multi_add_handle(curlm, slot->curl);
 	int num_transfers;
 
 	if (curlm_result != CURLM_OK &&
 	    curlm_result != CURLM_CALL_MULTI_PERFORM) {
+		warning("curl_multi_add_handle failed: %s",
+			curl_multi_strerror(curlm_result));
 		active_requests--;
 		slot->in_use = 0;
 		return 0;
 	}
 
 	/*
