static int wm_write(const data_set_t *ds, /* {{{ */
                    const value_list_t *vl, user_data_t *ud) {
  wm_node_t *node = ud->data;
  mongoc_collection_t *collection = NULL;
  bson_t *bson_record;
  bson_error_t error;
  int status;

  bson_record = wm_create_bson(ds, vl, node->store_rates);
  if (!bson_record) {
    ERROR("write_mongodb plugin: error making insert bson");
    return -1;
  }

  pthread_mutex_lock(&node->lock);
  if (wm_initialize(node) < 0) {
    ERROR("write_mongodb plugin: error making connection to server");
    pthread_mutex_unlock(&node->lock);
    bson_destroy(bson_record);
    return -1;
  }

  collection =
      mongoc_client_get_collection(node->client, "collectd", vl->plugin);
  if (!collection) {
    ERROR("write_mongodb plugin: error creating/getting collection");
    mongoc_database_destroy(node->database);
    mongoc_client_destroy(node->client);
    node->database = NULL;
    node->client = NULL;
    node->connected = 0;
    pthread_mutex_unlock(&node->lock);
    bson_destroy(bson_record);
    return -1;
  }

  status = mongoc_collection_insert(collection, MONGOC_INSERT_NONE, bson_record,
                                    NULL, &error);

  if (!status) {
    ERROR("write_mongodb plugin: error inserting record: %s", error.message);
    mongoc_database_destroy(node->database);
    mongoc_client_destroy(node->client);
    node->database = NULL;
    node->client = NULL;
    node->connected = 0;
    pthread_mutex_unlock(&node->lock);
    bson_destroy(bson_record);
    mongoc_collection_destroy(collection);
    return -1;
  }

  /* free our resource as not to leak memory */
  mongoc_collection_destroy(collection);

  pthread_mutex_unlock(&node->lock);

  bson_destroy(bson_record);

  return 0;
}