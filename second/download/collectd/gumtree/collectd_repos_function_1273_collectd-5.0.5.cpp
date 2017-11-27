static int cx_init_curl (cx_t *db) /* {{{ */
{
  db->curl = curl_easy_init ();
  if (db->curl == NULL)
  {
    ERROR ("curl_xml plugin: curl_easy_init failed.");
    return (-1);
  }

  curl_easy_setopt (db->curl, CURLOPT_NOSIGNAL, 1);
  curl_easy_setopt (db->curl, CURLOPT_WRITEFUNCTION, cx_curl_callback);
  curl_easy_setopt (db->curl, CURLOPT_WRITEDATA, db);
  curl_easy_setopt (db->curl, CURLOPT_USERAGENT,
                    PACKAGE_NAME"/"PACKAGE_VERSION);
  curl_easy_setopt (db->curl, CURLOPT_ERRORBUFFER, db->curl_errbuf);
  curl_easy_setopt (db->curl, CURLOPT_URL, db->url);

  if (db->user != NULL)
  {
    size_t credentials_size;

    credentials_size = strlen (db->user) + 2;
    if (db->pass != NULL)
      credentials_size += strlen (db->pass);

    db->credentials = (char *) malloc (credentials_size);
    if (db->credentials == NULL)
    {
      ERROR ("curl_xml plugin: malloc failed.");
      return (-1);
    }

    ssnprintf (db->credentials, credentials_size, "%s:%s",
               db->user, (db->pass == NULL) ? "" : db->pass);
    curl_easy_setopt (db->curl, CURLOPT_USERPWD, db->credentials);
  }

  curl_easy_setopt (db->curl, CURLOPT_SSL_VERIFYPEER, db->verify_peer ? 1L : 0L);
  curl_easy_setopt (db->curl, CURLOPT_SSL_VERIFYHOST,
                    db->verify_host ? 2L : 0L);
  if (db->cacert != NULL)
    curl_easy_setopt (db->curl, CURLOPT_CAINFO, db->cacert);

  return (0);
}