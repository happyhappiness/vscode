static int bind_init (void) /* {{{ */
{
  if (curl != NULL)
    return (0);

  curl = curl_easy_init ();
  if (curl == NULL)
  {
    ERROR ("bind plugin: bind_init: curl_easy_init failed.");
    return (-1);
  }

  curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, bind_curl_callback);
  curl_easy_setopt (curl, CURLOPT_USERAGENT, PACKAGE_NAME"/"PACKAGE_VERSION);
  curl_easy_setopt (curl, CURLOPT_ERRORBUFFER, bind_curl_error);
  curl_easy_setopt (curl, CURLOPT_URL, (url != NULL) ? url : BIND_DEFAULT_URL);
  curl_easy_setopt (curl, CURLOPT_FOLLOWLOCATION, 1);

  return (0);
}