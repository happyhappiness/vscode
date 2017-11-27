static int cj_cb_string (void *ctx, const unsigned char *val,
                           unsigned int len)
{
  cj_t *db = (cj_t *)ctx;
  c_avl_tree_t *tree;
  char *ptr;

  if (db->depth != 1) /* e.g. _all_dbs */
    return 1;

  cj_cb_map_key (ctx, val, len); /* same logic */

  tree = db->state[db->depth].tree;

  if ((tree != NULL) && (ptr = rindex (db->url, '/')))
  {
    char url[PATH_MAX];
    CURL *curl;

    /* url =~ s,[^/]+$,$name, */
    len = (ptr - db->url) + 1;
    ptr = url;
    sstrncpy (ptr, db->url, sizeof (url));
    sstrncpy (ptr + len, db->state[db->depth].name, sizeof (url) - len);

    curl = curl_easy_duphandle (db->curl);
    curl_easy_setopt (curl, CURLOPT_URL, url);
    cj_curl_perform (db, curl);
    curl_easy_cleanup (curl);
  }
  return 1;
}