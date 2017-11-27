static int init (void)
{
	static char credentials[1024];

	if (curl != NULL)
	{
		curl_easy_cleanup (curl);
	}

	if ((curl = curl_easy_init ()) == NULL)
	{
		ERROR ("apache: `curl_easy_init' failed.");
		return (-1);
	}

	curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, apache_curl_callback);
	curl_easy_setopt (curl, CURLOPT_USERAGENT, PACKAGE_NAME"/"PACKAGE_VERSION);
	curl_easy_setopt (curl, CURLOPT_ERRORBUFFER, apache_curl_error);

	if (user != NULL)
	{
		if (snprintf (credentials, 1024, "%s:%s", user, pass == NULL ? "" : pass) >= 1024)
		{
			ERROR ("apache: Credentials would have been truncated.");
			return (-1);
		}

		curl_easy_setopt (curl, CURLOPT_USERPWD, credentials);
	}

	if (url != NULL)
	{
		curl_easy_setopt (curl, CURLOPT_URL, url);
	}

	if (cacert != NULL)
	{
		curl_easy_setopt (curl, CURLOPT_CAINFO, cacert);
	}

	return (0);
}