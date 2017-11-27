static int cj_perform(cj_t *db) /* {{{ */
{
  int status;
  yajl_handle yprev = db->yajl;

  db->yajl = yajl_alloc(&ycallbacks,
#if HAVE_YAJL_V2
                        /* alloc funcs = */ NULL,
#else
                        /* alloc funcs = */ NULL, NULL,
#endif
                        /* context = */ (void *)db);
  if (db->yajl == NULL) {
    ERROR("curl_json plugin: yajl_alloc failed.");
    db->yajl = yprev;
    return -1;
  }

  if (db->url)
    status = cj_curl_perform(db);
  else
    status = cj_sock_perform(db);
  if (status < 0) {
    yajl_free(db->yajl);
    db->yajl = yprev;
    return -1;
  }

#if HAVE_YAJL_V2
  status = yajl_complete_parse(db->yajl);
#else
  status = yajl_parse_complete(db->yajl);
#endif
  if (status != yajl_status_ok) {
    unsigned char *errmsg;

    errmsg = yajl_get_error(db->yajl, /* verbose = */ 0,
                            /* jsonText = */ NULL, /* jsonTextLen = */ 0);
    ERROR("curl_json plugin: yajl_parse_complete failed: %s", (char *)errmsg);
    yajl_free_error(db->yajl, errmsg);
    yajl_free(db->yajl);
    db->yajl = yprev;
    return -1;
  }

  yajl_free(db->yajl);
  db->yajl = yprev;
  return 0;
}