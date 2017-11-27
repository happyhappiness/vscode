static int init (void)
{
	static char credentials[1024];

	if (url == NULL)
	{
		WARNING ("apache plugin: init: No URL configured, returning "
				"an error.");
		return (-1);
	}

	if (curl != NULL)
	{
		curl_easy_cleanup (curl);
	}

	if ((curl = curl_easy_init ()) == NULL)
	{
		ERROR ("apache plugin: init: `curl_easy_init' failed.");
		return (-1);
	}

	curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, apache_curl_callback);
	curl_easy_setopt (curl, CURLOPT_USERAGENT, PACKAGE_NAME"/"PACKAGE_VERSION);
	curl_easy_setopt (curl, CURLOPT_ERRORBUFFER, apache_curl_error);

	if (user != NULL)
	{
		int status;

		status = ssnprintf (credentials, sizeof (credentials), "%s:%s",
				user, (pass == NULL) ? "" : pass);
		if ((status < 0) || ((size_t) status >= sizeof (credentials)))
		{
			ERROR ("apache plugin: init: Returning an error "
					"because the credentials have been "
					"truncated.");
			return (-1);
		}

		curl_easy_setopt (curl, CURLOPT_USERPWD, credentials);
	}

	curl_easy_setopt (curl, CURLOPT_URL, url);

	if ((verify_peer == NULL) || (strcmp (verify_peer, "true") == 0))
	{
		curl_easy_setopt (curl, CURLOPT_SSL_VERIFYPEER, 1);
	}
	else
	{
		curl_easy_setopt (curl, CURLOPT_SSL_VERIFYPEER, 0);
	}

	if ((verify_host == NULL) || (strcmp (verify_host, "true") == 0))
	{
		curl_easy_setopt (curl, CURLOPT_SSL_VERIFYHOST, 2);
	}
	else
	{
		curl_easy_setopt (curl, CURLOPT_SSL_VERIFYHOST, 0);
	}

	if (cacert != NULL)
	{
		curl_easy_setopt (curl, CURLOPT_CAINFO, cacert);
	}

	return (0);
}