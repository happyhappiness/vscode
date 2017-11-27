static int cx_curl_perform (cx_t *db, CURL *curl) /* {{{ */
{
  int status;
  long rc;
  char *ptr;
  char *url;

  db->buffer_fill = 0; 
  status = curl_easy_perform (curl);

  curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);
  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &rc);

  /* The response code is zero if a non-HTTP transport was used. */
  if ((rc != 0) && (rc != 200))
  {
    ERROR ("curl_xml plugin: curl_easy_perform failed with response code %ld (%s)",
           rc, url);
    return (-1);
  }

  if (status != 0)
  {
    ERROR ("curl_xml plugin: curl_easy_perform failed with status %i: %s (%s)",
           status, db->curl_errbuf, url);
    return (-1);
  }

  ptr = db->buffer;

  status = cx_parse_stats_xml(BAD_CAST ptr, db);
  db->buffer_fill = 0;

  return status;
}