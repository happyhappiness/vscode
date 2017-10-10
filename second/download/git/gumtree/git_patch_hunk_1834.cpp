 	http_is_verbose = 0;
 	normalized_url = url_normalize(url, &config.url);
 
 	git_config(urlmatch_config_entry, &config);
 	free(normalized_url);
 
-	curl_global_init(CURL_GLOBAL_ALL);
+	if (curl_global_init(CURL_GLOBAL_ALL) != CURLE_OK)
+		die("curl_global_init failed");
 
 	http_proactive_auth = proactive_auth;
 
 	if (remote && remote->http_proxy)
 		curl_http_proxy = xstrdup(remote->http_proxy);
 
