static void cx_free(void *arg) /* {{{ */
{
  cx_t *db;

  DEBUG("curl_xml plugin: cx_free (arg = %p);", arg);

  db = (cx_t *)arg;

  if (db == NULL)
    return;

  if (db->curl != NULL)
    curl_easy_cleanup(db->curl);
  db->curl = NULL;

  if (db->xpath_list != NULL)
    cx_xpath_list_free(db->xpath_list);

  sfree(db->buffer);
  sfree(db->instance);
  sfree(db->plugin_name);
  sfree(db->host);

  sfree(db->url);
  sfree(db->user);
  sfree(db->pass);
  sfree(db->credentials);
  sfree(db->cacert);
  sfree(db->post_body);
  curl_slist_free_all(db->headers);
  curl_stats_destroy(db->stats);

  for (size_t i = 0; i < db->namespaces_num; i++) {
    sfree(db->namespaces[i].prefix);
    sfree(db->namespaces[i].url);
  }
  sfree(db->namespaces);

  sfree(db);
}