 				 curl_low_speed_limit);
 		curl_easy_setopt(result, CURLOPT_LOW_SPEED_TIME,
 				 curl_low_speed_time);
 	}
 
 	curl_easy_setopt(result, CURLOPT_FOLLOWLOCATION, 1);
-	curl_easy_setopt(result, CURLOPT_MAXREDIRS, 20);
 #if LIBCURL_VERSION_NUM >= 0x071301
 	curl_easy_setopt(result, CURLOPT_POSTREDIR, CURL_REDIR_POST_ALL);
 #elif LIBCURL_VERSION_NUM >= 0x071101
 	curl_easy_setopt(result, CURLOPT_POST301, 1);
 #endif
-#if LIBCURL_VERSION_NUM >= 0x071304
-	if (is_transport_allowed("http"))
-		allowed_protocols |= CURLPROTO_HTTP;
-	if (is_transport_allowed("https"))
-		allowed_protocols |= CURLPROTO_HTTPS;
-	if (is_transport_allowed("ftp"))
-		allowed_protocols |= CURLPROTO_FTP;
-	if (is_transport_allowed("ftps"))
-		allowed_protocols |= CURLPROTO_FTPS;
-	curl_easy_setopt(result, CURLOPT_REDIR_PROTOCOLS, allowed_protocols);
-#else
-	if (transport_restrict_protocols())
-		warning("protocol restrictions not applied to curl redirects because\n"
-			"your curl version is too old (>= 7.19.4)");
-#endif
 
 	if (getenv("GIT_CURL_VERBOSE"))
 		curl_easy_setopt(result, CURLOPT_VERBOSE, 1);
 
 	curl_easy_setopt(result, CURLOPT_USERAGENT,
 		user_agent ? user_agent : git_user_agent());
