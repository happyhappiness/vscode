static int cj_curl_perform (cj_t *db, CURL *curl) /* {{{ */
{
  int status;
  long rc;
  char *url;
  yajl_handle yprev = db->yajl;

  db->yajl = yajl_alloc (&ycallbacks,
#if HAVE_YAJL_V2
      /* alloc funcs = */ NULL,
#else
      /* alloc funcs = */ NULL, NULL,
#endif
      /* context = */ (void *)db);
  if (db->yajl == NULL)
  {
    ERROR ("curl_json plugin: yajl_alloc failed.");
    db->yajl = yprev;
    return (-1);
  }

  url = NULL;
  curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);

  status = curl_easy_perform (curl);
  if (status != 0)
  {
    ERROR ("curl_json plugin: curl_easy_perform failed with status %i: %s (%s)",
           status, db->curl_errbuf, (url != NULL) ? url : "<null>");
    yajl_free (db->yajl);
    db->yajl = yprev;
    return (-1);
  }

  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &rc);

  /* The response code is zero if a non-HTTP transport was used. */
  if ((rc != 0) && (rc != 200))
  {
    ERROR ("curl_json plugin: curl_easy_perform failed with "
        "response code %ld (%s)", rc, url);
    yajl_free (db->yajl);
    db->yajl = yprev;
    return (-1);
  }

#if HAVE_YAJL_V2
    status = yajl_complete_parse(db->yajl);
#else
    status = yajl_parse_complete(db->yajl);
#endif
  if (status != yajl_status_ok)
  {
    unsigned char *errmsg;

    errmsg = yajl_get_error (db->yajl, /* verbose = */ 0,
        /* jsonText = */ NULL, /* jsonTextLen = */ 0);
    ERROR ("curl_json plugin: yajl_parse_complete failed: %s",
        (char *) errmsg);
    yajl_free_error (db->yajl, errmsg);
    yajl_free (db->yajl);
    db->yajl = yprev;
    return (-1);
  }

  yajl_free (db->yajl);
  db->yajl = yprev;
  return (0);
}