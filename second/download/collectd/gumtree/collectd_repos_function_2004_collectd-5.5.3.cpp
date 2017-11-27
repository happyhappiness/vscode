static int cj_curl_perform(cj_t *db) /* {{{ */
{
  int status;
  long rc;
  char *url;
  url = db->url;

  status = curl_easy_perform (db->curl);
  if (status != CURLE_OK)
  {
    ERROR ("curl_json plugin: curl_easy_perform failed with status %i: %s (%s)",
           status, db->curl_errbuf, url);
    return (-1);
  }

  curl_easy_getinfo(db->curl, CURLINFO_EFFECTIVE_URL, &url);
  curl_easy_getinfo(db->curl, CURLINFO_RESPONSE_CODE, &rc);

  /* The response code is zero if a non-HTTP transport was used. */
  if ((rc != 0) && (rc != 200))
  {
    ERROR ("curl_json plugin: curl_easy_perform failed with "
        "response code %ld (%s)", rc, url);
    return (-1);
  }
  return (0);
}