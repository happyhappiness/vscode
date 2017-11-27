static int cj_curl_perform (cj_t *db, CURL *curl) /* {{{ */
{
  int status;
  long rc;
  char *url;
  yajl_handle yprev = db->yajl;

  db->yajl = yajl_alloc (&ycallbacks, NULL, NULL, (void *)db);
  if (db->yajl == NULL)
  {
    ERROR ("curl_json plugin: yajl_alloc failed.");
    db->yajl = yprev;
    return (-1);
  }

  status = curl_easy_perform (curl);

  yajl_free (db->yajl);
  db->yajl = yprev;

  curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);
  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &rc);

  /* The response code is zero if a non-HTTP transport was used. */
  if ((rc != 0) && (rc != 200))
  {
    ERROR ("curl_json plugin: curl_easy_perform failed with response code %ld (%s)",
           rc, url);
    return (-1);
  }

  if (status != 0)
  {
    ERROR ("curl_json plugin: curl_easy_perform failed with status %i: %s (%s)",
           status, db->curl_errbuf, url);
    return (-1);
  }

  return (0);
}