static int cc_page_init_curl (web_page_t *wp) /* {{{ */
{
  wp->curl = curl_easy_init ();
  if (wp->curl == NULL)
  {
    ERROR ("curl plugin: curl_easy_init failed.");
    return (-1);
  }

  curl_easy_setopt (wp->curl, CURLOPT_WRITEFUNCTION, cc_curl_callback);
  curl_easy_setopt (wp->curl, CURLOPT_WRITEDATA, wp);
  curl_easy_setopt (wp->curl, CURLOPT_USERAGENT,
      PACKAGE_NAME"/"PACKAGE_VERSION);
  curl_easy_setopt (wp->curl, CURLOPT_ERRORBUFFER, wp->curl_errbuf);
  curl_easy_setopt (wp->curl, CURLOPT_URL, wp->url);

  if (wp->user != NULL)
  {
    size_t credentials_size;

    credentials_size = strlen (wp->user) + 2;
    if (wp->pass != NULL)
      credentials_size += strlen (wp->pass);

    wp->credentials = (char *) malloc (credentials_size);
    if (wp->credentials == NULL)
    {
      ERROR ("curl plugin: malloc failed.");
      return (-1);
    }

    ssnprintf (wp->credentials, credentials_size, "%s:%s",
        wp->user, (wp->pass == NULL) ? "" : wp->pass);
    curl_easy_setopt (wp->curl, CURLOPT_USERPWD, wp->credentials);
  }

  curl_easy_setopt (wp->curl, CURLOPT_SSL_VERIFYPEER, wp->verify_peer);
  curl_easy_setopt (wp->curl, CURLOPT_SSL_VERIFYHOST,
      wp->verify_host ? 2 : 0);
  if (wp->cacert != NULL)
    curl_easy_setopt (wp->curl, CURLOPT_CAINFO, wp->cacert);

  return (0);
}