static int cx_read(user_data_t *ud) /* {{{ */
{
  if ((ud == NULL) || (ud->data == NULL)) {
    ERROR("curl_xml plugin: cx_read: Invalid user data.");
    return -1;
  }

  long rc;
  char *url;
  cx_t *db = (cx_t *)ud->data;

  db->buffer_fill = 0;

  curl_easy_setopt(db->curl, CURLOPT_URL, db->url);

  int status = curl_easy_perform(db->curl);
  if (status != CURLE_OK) {
    ERROR("curl_xml plugin: curl_easy_perform failed with status %i: %s (%s)",
          status, db->curl_errbuf, db->url);
    return -1;
  }
  if (db->stats != NULL)
    curl_stats_dispatch(db->stats, db->curl, cx_host(db), "curl_xml",
                        db->instance);

  curl_easy_getinfo(db->curl, CURLINFO_EFFECTIVE_URL, &url);
  curl_easy_getinfo(db->curl, CURLINFO_RESPONSE_CODE, &rc);

  /* The response code is zero if a non-HTTP transport was used. */
  if ((rc != 0) && (rc != 200)) {
    ERROR(
        "curl_xml plugin: curl_easy_perform failed with response code %ld (%s)",
        rc, url);
    return -1;
  }

  status = cx_parse_xml(db, db->buffer);
  db->buffer_fill = 0;

  return status;
}