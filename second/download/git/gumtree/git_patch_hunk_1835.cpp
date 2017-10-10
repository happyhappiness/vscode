 		char *http_max_requests = getenv("GIT_HTTP_MAX_REQUESTS");
 		if (http_max_requests != NULL)
 			max_requests = atoi(http_max_requests);
 	}
 
 	curlm = curl_multi_init();
-	if (curlm == NULL) {
-		fprintf(stderr, "Error creating curl multi handle.\n");
-		exit(1);
-	}
+	if (!curlm)
+		die("curl_multi_init failed");
 #endif
 
 	if (getenv("GIT_SSL_NO_VERIFY"))
 		curl_ssl_verify = 0;
 
 	set_from_env(&ssl_cert, "GIT_SSL_CERT");
