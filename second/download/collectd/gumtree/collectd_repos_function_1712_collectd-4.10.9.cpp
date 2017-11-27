static void cj_free (void *arg) /* {{{ */
{
  cj_t *db;

  DEBUG ("curl_json plugin: cj_free (arg = %p);", arg);

  db = (cj_t *) arg;

  if (db == NULL)
    return;

  if (db->curl != NULL)
    curl_easy_cleanup (db->curl);
  db->curl = NULL;

  if (db->tree != NULL)
    cj_tree_free (db->tree);
  db->tree = NULL;

  sfree (db->instance);
  sfree (db->host);

  sfree (db->url);
  sfree (db->user);
  sfree (db->pass);
  sfree (db->credentials);
  sfree (db->cacert);

  sfree (db);
}