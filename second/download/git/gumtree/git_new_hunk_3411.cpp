#else
		warning(_("Public key pinning not supported with cURL < 7.44.0"));
		return 0;
#endif
	}

	if (!strcmp("http.extraheader", var)) {
		if (!value) {
			return config_error_nonbool(var);
		} else if (!*value) {
			curl_slist_free_all(extra_http_headers);
			extra_http_headers = NULL;
		} else {
			extra_http_headers =
				curl_slist_append(extra_http_headers, value);
		}
		return 0;
	}

	/* Fall back on the default ones */
	return git_default_config(var, value, cb);
}

static void init_curl_http_auth(CURL *result)
{
