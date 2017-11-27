static int init (void)
{
  if (curl != NULL)
    curl_easy_cleanup (curl);

  if ((curl = curl_easy_init ()) == NULL)
  {
    ERROR ("nginx plugin: curl_easy_init failed.");
    return (-1);
  }

  curl_easy_setopt (curl, CURLOPT_NOSIGNAL, 1L);
  curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, nginx_curl_callback);
  curl_easy_setopt (curl, CURLOPT_USERAGENT, COLLECTD_USERAGENT);
  curl_easy_setopt (curl, CURLOPT_ERRORBUFFER, nginx_curl_error);

  if (user != NULL)
  {
#ifdef HAVE_CURLOPT_USERNAME
    curl_easy_setopt (curl, CURLOPT_USERNAME, user);
    curl_easy_setopt (curl, CURLOPT_PASSWORD, (pass == NULL) ? "" : pass);
#else
    static char credentials[1024];
    int status = ssnprintf (credentials, sizeof (credentials),
	"%s:%s", user, pass == NULL ? "" : pass);
    if ((status < 0) || ((size_t) status >= sizeof (credentials)))
    {
      ERROR ("nginx plugin: Credentials would have been truncated.");
      return (-1);
    }

    curl_easy_setopt (curl, CURLOPT_USERPWD, credentials);
#endif
  }

  if (url != NULL)
  {
    curl_easy_setopt (curl, CURLOPT_URL, url);
  }

  curl_easy_setopt (curl, CURLOPT_FOLLOWLOCATION, 1L);
  curl_easy_setopt (curl, CURLOPT_MAXREDIRS, 50L);

  if ((verify_peer == NULL) || IS_TRUE (verify_peer))
  {
    curl_easy_setopt (curl, CURLOPT_SSL_VERIFYPEER, 1L);
  }
  else
  {
    curl_easy_setopt (curl, CURLOPT_SSL_VERIFYPEER, 0L);
  }

  if ((verify_host == NULL) || IS_TRUE (verify_host))
  {
    curl_easy_setopt (curl, CURLOPT_SSL_VERIFYHOST, 2L);
  }
  else
  {
    curl_easy_setopt (curl, CURLOPT_SSL_VERIFYHOST, 0L);
  }

  if (cacert != NULL)
  {
    curl_easy_setopt (curl, CURLOPT_CAINFO, cacert);
  }

#ifdef HAVE_CURLOPT_TIMEOUT_MS
  if (timeout != NULL)
  {
    curl_easy_setopt (curl, CURLOPT_TIMEOUT_MS, atol(timeout));
  }
  else
  {
    curl_easy_setopt (curl, CURLOPT_TIMEOUT_MS, (long) CDTIME_T_TO_MS(plugin_get_interval()));
  }
#endif

  return (0);
}