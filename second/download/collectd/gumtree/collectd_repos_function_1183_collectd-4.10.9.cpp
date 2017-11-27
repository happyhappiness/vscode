static void cx_free (void *arg) /* {{{ */
{
  cx_t *db;

  DEBUG ("curl_xml plugin: cx_free (arg = %p);", arg);

  db = (cx_t *) arg;

  if (db == NULL)
    return;

  if (db->curl != NULL)
    curl_easy_cleanup (db->curl);
  db->curl = NULL;

  if (db->list != NULL)
    cx_list_free (db->list);

  sfree (db->buffer);
  sfree (db->instance);
  sfree (db->host);

  sfree (db->url);
  sfree (db->user);
  sfree (db->pass);
  sfree (db->credentials);
  sfree (db->cacert);

  sfree (db);
}