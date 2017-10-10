 	curl_easy_setopt(result, CURLOPT_REDIR_PROTOCOLS, allowed_protocols);
 #else
 	if (transport_restrict_protocols())
 		warning("protocol restrictions not applied to curl redirects because\n"
 			"your curl version is too old (>= 7.19.4)");
 #endif
-
 	if (getenv("GIT_CURL_VERBOSE"))
-		curl_easy_setopt(result, CURLOPT_VERBOSE, 1);
+		curl_easy_setopt(result, CURLOPT_VERBOSE, 1L);
+	setup_curl_trace(result);
 
 	curl_easy_setopt(result, CURLOPT_USERAGENT,
 		user_agent ? user_agent : git_user_agent());
 
 	if (curl_ftp_no_epsv)
 		curl_easy_setopt(result, CURLOPT_FTP_USE_EPSV, 0);
