static int init_host (apache_t *st) /* {{{ */
{
	assert (st->url != NULL);
	/* (Assured by `config_add') */

	if (st->curl != NULL)
	{
		curl_easy_cleanup (st->curl);
		st->curl = NULL;
	}

	if ((st->curl = curl_easy_init ()) == NULL)
	{
		ERROR ("apache plugin: init_host: `curl_easy_init' failed.");
		return (-1);
	}

	curl_easy_setopt (st->curl, CURLOPT_NOSIGNAL, 1L);
	curl_easy_setopt (st->curl, CURLOPT_WRITEFUNCTION, apache_curl_callback);
	curl_easy_setopt (st->curl, CURLOPT_WRITEDATA, st);

	/* not set as yet if the user specified string doesn't match apache or
	 * lighttpd, then ignore it. Headers will be parsed to find out the
	 * server type */
	st->server_type = -1;

	if (st->server != NULL)
	{
		if (strcasecmp(st->server, "apache") == 0)
			st->server_type = APACHE;
		else if (strcasecmp(st->server, "lighttpd") == 0)
			st->server_type = LIGHTTPD;
		else if (strcasecmp(st->server, "ibm_http_server") == 0)
			st->server_type = APACHE;
		else
			WARNING ("apache plugin: Unknown `Server' setting: %s",
					st->server);
	}

	/* if not found register a header callback to determine the server_type */
	if (st->server_type == -1)
	{
		curl_easy_setopt (st->curl, CURLOPT_HEADERFUNCTION, apache_header_callback);
		curl_easy_setopt (st->curl, CURLOPT_WRITEHEADER, st);
	}

	curl_easy_setopt (st->curl, CURLOPT_USERAGENT, COLLECTD_USERAGENT);
	curl_easy_setopt (st->curl, CURLOPT_ERRORBUFFER, st->apache_curl_error);

	if (st->user != NULL)
	{
#ifdef HAVE_CURLOPT_USERNAME
		curl_easy_setopt (st->curl, CURLOPT_USERNAME, st->user);
		curl_easy_setopt (st->curl, CURLOPT_PASSWORD,
				(st->pass == NULL) ? "" : st->pass);
#else
		static char credentials[1024];
		int status;

		status = ssnprintf (credentials, sizeof (credentials), "%s:%s",
				st->user, (st->pass == NULL) ? "" : st->pass);
		if ((status < 0) || ((size_t) status >= sizeof (credentials)))
		{
			ERROR ("apache plugin: init_host: Returning an error "
					"because the credentials have been "
					"truncated.");
			curl_easy_cleanup (st->curl);
			st->curl = NULL;
			return (-1);
		}

		curl_easy_setopt (st->curl, CURLOPT_USERPWD, credentials);
#endif
	}

	curl_easy_setopt (st->curl, CURLOPT_URL, st->url);
	curl_easy_setopt (st->curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt (st->curl, CURLOPT_MAXREDIRS, 50L);

	curl_easy_setopt (st->curl, CURLOPT_SSL_VERIFYPEER,
			(long) st->verify_peer);
	curl_easy_setopt (st->curl, CURLOPT_SSL_VERIFYHOST,
			st->verify_host ? 2L : 0L);
	if (st->cacert != NULL)
		curl_easy_setopt (st->curl, CURLOPT_CAINFO, st->cacert);
	if (st->ssl_ciphers != NULL)
		curl_easy_setopt (st->curl, CURLOPT_SSL_CIPHER_LIST,st->ssl_ciphers);

#ifdef HAVE_CURLOPT_TIMEOUT_MS
	if (st->timeout >= 0)
		curl_easy_setopt (st->curl, CURLOPT_TIMEOUT_MS, (long) st->timeout);
	else
		curl_easy_setopt (st->curl, CURLOPT_TIMEOUT_MS,
				CDTIME_T_TO_MS(plugin_get_interval()));
#endif

	return (0);
}