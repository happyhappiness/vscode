static int cj_init_curl(cj_t *db) /* {{{ */
{
  db->curl = curl_easy_init();
  if (db->curl == NULL) {
    ERROR("curl_json plugin: curl_easy_init failed.");
    return (-1);
  }

  curl_easy_setopt(db->curl, CURLOPT_NOSIGNAL, 1L);
  curl_easy_setopt(db->curl, CURLOPT_WRITEFUNCTION, cj_curl_callback);
  curl_easy_setopt(db->curl, CURLOPT_WRITEDATA, db);
  curl_easy_setopt(db->curl, CURLOPT_USERAGENT, COLLECTD_USERAGENT);
  curl_easy_setopt(db->curl, CURLOPT_ERRORBUFFER, db->curl_errbuf);
  curl_easy_setopt(db->curl, CURLOPT_FOLLOWLOCATION, 1L);
  curl_easy_setopt(db->curl, CURLOPT_MAXREDIRS, 50L);

  if (db->user != NULL) {
#ifdef HAVE_CURLOPT_USERNAME
    curl_easy_setopt(db->curl, CURLOPT_USERNAME, db->user);
    curl_easy_setopt(db->curl, CURLOPT_PASSWORD,
                     (db->pass == NULL) ? "" : db->pass);
#else
    size_t credentials_size;

    credentials_size = strlen(db->user) + 2;
    if (db->pass != NULL)
      credentials_size += strlen(db->pass);

    db->credentials = malloc(credentials_size);
    if (db->credentials == NULL) {
      ERROR("curl_json plugin: malloc failed.");
      return (-1);
    }

    ssnprintf(db->credentials, credentials_size, "%s:%s", db->user,
              (db->pass == NULL) ? "" : db->pass);
    curl_easy_setopt(db->curl, CURLOPT_USERPWD, db->credentials);
#endif

    if (db->digest)
      curl_easy_setopt(db->curl, CURLOPT_HTTPAUTH, CURLAUTH_DIGEST);
  }

  curl_easy_setopt(db->curl, CURLOPT_SSL_VERIFYPEER, (long)db->verify_peer);
  curl_easy_setopt(db->curl, CURLOPT_SSL_VERIFYHOST, db->verify_host ? 2L : 0L);
  if (db->cacert != NULL)
    curl_easy_setopt(db->curl, CURLOPT_CAINFO, db->cacert);
  if (db->headers != NULL)
    curl_easy_setopt(db->curl, CURLOPT_HTTPHEADER, db->headers);
  if (db->post_body != NULL)
    curl_easy_setopt(db->curl, CURLOPT_POSTFIELDS, db->post_body);

#ifdef HAVE_CURLOPT_TIMEOUT_MS
  if (db->timeout >= 0)
    curl_easy_setopt(db->curl, CURLOPT_TIMEOUT_MS, (long)db->timeout);
  else if (db->interval > 0)
    curl_easy_setopt(db->curl, CURLOPT_TIMEOUT_MS,
                     (long)CDTIME_T_TO_MS(db->interval));
  else
    curl_easy_setopt(db->curl, CURLOPT_TIMEOUT_MS,
                     (long)CDTIME_T_TO_MS(plugin_get_interval()));
#endif

  return (0);
}