static int init (void)
{
  static char credentials[1024];

  if (curl != NULL)
    curl_easy_cleanup (curl);

  if ((curl = curl_easy_init ()) == NULL)
  {
    ERROR ("nginx plugin: curl_easy_init failed.");
    return (-1);
  }

  curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, nginx_curl_callback);
  curl_easy_setopt (curl, CURLOPT_USERAGENT, PACKAGE_NAME"/"PACKAGE_VERSION);
  curl_easy_setopt (curl, CURLOPT_ERRORBUFFER, nginx_curl_error);

  if (user != NULL)
  {
    if (snprintf (credentials, 1024, "%s:%s", user, pass == NULL ? "" : pass) >= 1024)
    {
      ERROR ("nginx plugin: Credentials would have been truncated.");
      return (-1);
    }

    curl_easy_setopt (curl, CURLOPT_USERPWD, credentials);
  }

  if (url != NULL)
  {
    curl_easy_setopt (curl, CURLOPT_URL, url);
  }

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