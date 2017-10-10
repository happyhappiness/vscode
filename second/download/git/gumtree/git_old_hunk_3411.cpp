#else
		warning(_("Public key pinning not supported with cURL < 7.44.0"));
		return 0;
#endif
	}

	/* Fall back on the default ones */
	return git_default_config(var, value, cb);
}

static void init_curl_http_auth(CURL *result)
{
