static int wm_initialize(wm_node_t *node) /* {{{ */
{
  char *uri;

  if (node->connected)
    return 0;

  INFO("write_mongodb plugin: Connecting to [%s]:%d", node->host, node->port);

  if ((node->db != NULL) && (node->user != NULL) && (node->passwd != NULL)) {
    uri = ssnprintf_alloc("mongodb://%s:%s@%s:%d/?authSource=%s", node->user,
                          node->passwd, node->host, node->port, node->db);
    if (uri == NULL) {
      ERROR("write_mongodb plugin: Not enough memory to assemble "
            "authentication string.");
      mongoc_client_destroy(node->client);
      node->client = NULL;
      node->connected = 0;
      return -1;
    }

    node->client = mongoc_client_new(uri);
    if (!node->client) {
      ERROR("write_mongodb plugin: Authenticating to [%s]:%d for database "
            "\"%s\" as user \"%s\" failed.",
            node->host, node->port, node->db, node->user);
      node->connected = 0;
      sfree(uri);
      return -1;
    }
  } else {
    uri = ssnprintf_alloc("mongodb://%s:%d", node->host, node->port);
    if (uri == NULL) {
      ERROR("write_mongodb plugin: Not enough memory to assemble "
            "authentication string.");
      mongoc_client_destroy(node->client);
      node->client = NULL;
      node->connected = 0;
      return -1;
    }

    node->client = mongoc_client_new(uri);
    if (!node->client) {
      ERROR("write_mongodb plugin: Connecting to [%s]:%d failed.", node->host,
            node->port);
      node->connected = 0;
      sfree(uri);
      return -1;
    }
    sfree(uri);
  }

  node->database = mongoc_client_get_database(node->client, "collectd");
  if (!node->database) {
    ERROR("write_mongodb plugin: error creating/getting database");
    mongoc_client_destroy(node->client);
    node->client = NULL;
    node->connected = 0;
    return -1;
  }

  node->connected = 1;
  return 0;
}