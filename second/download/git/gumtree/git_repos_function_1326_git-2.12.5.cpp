static int handle_curl_result(struct slot_results *results)
{
	/*
	 * If we see a failing http code with CURLE_OK, we have turned off
	 * FAILONERROR (to keep the server's custom error response), and should
	 * translate the code into failure here.
	 *
	 * Likewise, if we see a redirect (30x code), that means we turned off
	 * redirect-following, and we should treat the result as an error.
	 */
	if (results->curl_result == CURLE_OK &&
	    results->http_code >= 300) {
		results->curl_result = CURLE_HTTP_RETURNED_ERROR;
		/*
		 * Normally curl will already have put the "reason phrase"
		 * from the server into curl_errorstr; unfortunately without
		 * FAILONERROR it is lost, so we can give only the numeric
		 * status code.
		 */
		snprintf(curl_errorstr, sizeof(curl_errorstr),
			 "The requested URL returned error: %ld",
			 results->http_code);
	}

	if (results->curl_result == CURLE_OK) {
		credential_approve(&http_auth);
		if (proxy_auth.password)
			credential_approve(&proxy_auth);
		return HTTP_OK;
	} else if (missing_target(results))
		return HTTP_MISSING_TARGET;
	else if (results->http_code == 401) {
		if (http_auth.username && http_auth.password) {
			credential_reject(&http_auth);
			return HTTP_NOAUTH;
		} else {
#ifdef LIBCURL_CAN_HANDLE_AUTH_ANY
			http_auth_methods &= ~CURLAUTH_GSSNEGOTIATE;
			if (results->auth_avail) {
				http_auth_methods &= results->auth_avail;
				http_auth_methods_restricted = 1;
			}
#endif
			return HTTP_REAUTH;
		}
	} else {
		if (results->http_connectcode == 407)
			credential_reject(&proxy_auth);
#if LIBCURL_VERSION_NUM >= 0x070c00
		if (!curl_errorstr[0])
			strlcpy(curl_errorstr,
				curl_easy_strerror(results->curl_result),
				sizeof(curl_errorstr));
#endif
		return HTTP_ERROR;
	}
}