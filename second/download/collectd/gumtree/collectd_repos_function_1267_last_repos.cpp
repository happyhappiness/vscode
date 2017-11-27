static void wm_config_free(void *ptr) /* {{{ */
{
  wm_node_t *node = ptr;

  if (node == NULL)
    return;

  mongoc_database_destroy(node->database);
  mongoc_client_destroy(node->client);
  node->database = NULL;
  node->client = NULL;
  node->connected = 0;

  sfree(node->host);
  sfree(node);
}