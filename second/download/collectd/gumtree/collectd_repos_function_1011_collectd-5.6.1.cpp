static int cc_page_init_curl (web_page_t *wp) /* {{{ */
{
  wp->curl = curl_easy_init ();
  if (wp->curl == NULL)
  {
    ERROR ("curl plugin: curl_easy_init failed.");
    return (-1);
  }

  curl_easy_setopt (wp->curl, CURLOPT_NOSIGNAL, 1L);
  curl_easy_setopt (wp->curl, CURLOPT_WRITEFUNCTION, cc_curl_callback);
  curl_easy_setopt (wp->curl, CURLOPT_WRITEDATA, wp);
  curl_easy_setopt (wp->curl, CURLOPT_USERAGENT, COLLECTD_USERAGENT);
  curl_easy_setopt (wp->curl, CURLOPT_ERRORBUFFER, wp->curl_errbuf);
  curl_easy_setopt (wp->curl, CURLOPT_URL, wp->url);
  curl_easy_setopt (wp->curl, CURLOPT_FOLLOWLOCATION, 1L);
  curl_easy_setopt (wp->curl, CURLOPT_MAXREDIRS, 50L);

  if (wp->user != NULL)
  {
#ifdef HAVE_CURLOPT_USERNAME
    curl_easy_setopt (wp->curl, CURLOPT_USERNAME, wp->user);
    curl_easy_setopt (wp->curl, CURLOPT_PASSWORD,
        (wp->pass == NULL) ? "" : wp->pass);
#else
    size_t credentials_size;

    credentials_size = strlen (wp->user) + 2;
    if (wp->pass != NULL)
      credentials_size += strlen (wp->pass);

    wp->credentials = malloc (credentials_size);
    if (wp->credentials == NULL)
    {
      ERROR ("curl plugin: malloc failed.");
      return (-1);
    }

    ssnprintf (wp->credentials, credentials_size, "%s:%s",
        wp->user, (wp->pass == NULL) ? "" : wp->pass);
    curl_easy_setopt (wp->curl, CURLOPT_USERPWD, wp->credentials);
#endif

    if (wp->digest)
      curl_easy_setopt (wp->curl, CURLOPT_HTTPAUTH, CURLAUTH_DIGEST);
  }

  curl_easy_setopt (wp->curl, CURLOPT_SSL_VERIFYPEER, (long) wp->verify_peer);
  curl_easy_setopt (wp->curl, CURLOPT_SSL_VERIFYHOST,
      wp->verify_host ? 2L : 0L);
  if (wp->cacert != NULL)
    curl_easy_setopt (wp->curl, CURLOPT_CAINFO, wp->cacert);
  if (wp->headers != NULL)
    curl_easy_setopt (wp->curl, CURLOPT_HTTPHEADER, wp->headers);
  if (wp->post_body != NULL)
    curl_easy_setopt (wp->curl, CURLOPT_POSTFIELDS, wp->post_body);

#ifdef HAVE_CURLOPT_TIMEOUT_MS
  if (wp->timeout >= 0)
    curl_easy_setopt (wp->curl, CURLOPT_TIMEOUT_MS, (long) wp->timeout);
  else
    curl_easy_setopt (wp->curl, CURLOPT_TIMEOUT_MS, (long) CDTIME_T_TO_MS(plugin_get_interval()));
#endif

  return (0);
}