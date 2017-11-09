static int curl_empty_auth_enabled(void)
{
	if (curl_empty_auth >= 0)
		return curl_empty_auth;

#ifndef LIBCURL_CAN_HANDLE_AUTH_ANY
	/*
	 * Our libcurl is too old to do AUTH_ANY in the first place;
	 * just default to turning the feature off.
	 */
#else
	/*
	 * In the automatic case, kick in the empty-auth
	 * hack as long as we would potentially try some
	 * method more exotic than "Basic" or "Digest".
	 *
	 * But only do this when this is our second or
	 * subsequent request, as by then we know what
	 * methods are available.
	 */
	if (http_auth_methods_restricted &&
	    (http_auth_methods & ~empty_auth_useless))
		return 1;
#endif
	return 0;
}