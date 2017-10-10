 #if LIBCURL_VERSION_NUM >= 0x071301
 	curl_easy_setopt(result, CURLOPT_POSTREDIR, CURL_REDIR_POST_ALL);
 #elif LIBCURL_VERSION_NUM >= 0x071101
 	curl_easy_setopt(result, CURLOPT_POST301, 1);
 #endif
 #if LIBCURL_VERSION_NUM >= 0x071304
-	if (is_transport_allowed("http"))
-		allowed_protocols |= CURLPROTO_HTTP;
-	if (is_transport_allowed("https"))
-		allowed_protocols |= CURLPROTO_HTTPS;
-	if (is_transport_allowed("ftp"))
-		allowed_protocols |= CURLPROTO_FTP;
-	if (is_transport_allowed("ftps"))
-		allowed_protocols |= CURLPROTO_FTPS;
-	curl_easy_setopt(result, CURLOPT_REDIR_PROTOCOLS, allowed_protocols);
-	curl_easy_setopt(result, CURLOPT_PROTOCOLS, allowed_protocols);
+	curl_easy_setopt(result, CURLOPT_REDIR_PROTOCOLS,
+			 get_curl_allowed_protocols(0));
+	curl_easy_setopt(result, CURLOPT_PROTOCOLS,
+			 get_curl_allowed_protocols(-1));
 #else
-	if (transport_restrict_protocols())
-		warning("protocol restrictions not applied to curl redirects because\n"
-			"your curl version is too old (>= 7.19.4)");
+	warning("protocol restrictions not applied to curl redirects because\n"
+		"your curl version is too old (>= 7.19.4)");
 #endif
 	if (getenv("GIT_CURL_VERBOSE"))
 		curl_easy_setopt(result, CURLOPT_VERBOSE, 1L);
 	setup_curl_trace(result);
 
 	curl_easy_setopt(result, CURLOPT_USERAGENT,
