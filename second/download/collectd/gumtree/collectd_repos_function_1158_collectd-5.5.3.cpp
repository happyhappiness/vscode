static int wm_write (const data_set_t *ds, /* {{{ */
    const value_list_t *vl,
    user_data_t *ud)
{
  wm_node_t *node = ud->data;
  char collection_name[512];
  bson *bson_record;
  int status;

  ssnprintf (collection_name, sizeof (collection_name), "collectd.%s",
      vl->plugin);

  bson_record = wm_create_bson (ds, vl, node->store_rates);
  if (bson_record == NULL)
    return (ENOMEM);

  pthread_mutex_lock (&node->lock);

  if (!mongo_is_connected (node->conn))
  {
    INFO ("write_mongodb plugin: Connecting to [%s]:%i",
        (node->host != NULL) ? node->host : "localhost",
        (node->port != 0) ? node->port : MONGO_DEFAULT_PORT);
    status = mongo_connect (node->conn, node->host, node->port);
    if (status != MONGO_OK) {
      ERROR ("write_mongodb plugin: Connecting to [%s]:%i failed.",
          (node->host != NULL) ? node->host : "localhost",
          (node->port != 0) ? node->port : MONGO_DEFAULT_PORT);
      mongo_destroy (node->conn);
      pthread_mutex_unlock (&node->lock);
      return (-1);
    }

    if ((node->db != NULL) && (node->user != NULL) && (node->passwd != NULL))
    {
      status = mongo_cmd_authenticate (node->conn,
          node->db, node->user, node->passwd);
      if (status != MONGO_OK)
      {
        ERROR ("write_mongodb plugin: Authenticating to [%s]%i for database "
            "\"%s\" as user \"%s\" failed.",
          (node->host != NULL) ? node->host : "localhost",
          (node->port != 0) ? node->port : MONGO_DEFAULT_PORT,
          node->db, node->user);
        mongo_destroy (node->conn);
        pthread_mutex_unlock (&node->lock);
        return (-1);
      }
    }

    if (node->timeout > 0) {
      status = mongo_set_op_timeout (node->conn, node->timeout);
      if (status != MONGO_OK) {
        WARNING ("write_mongodb plugin: mongo_set_op_timeout(%i) failed: %s",
            node->timeout, node->conn->errstr);
      }
    }
  }

  /* Assert if the connection has been established */
  assert (mongo_is_connected (node->conn));

  #if MONGO_MINOR >= 6
    /* There was an API change in 0.6.0 as linked below */
    /* https://github.com/mongodb/mongo-c-driver/blob/master/HISTORY.md */
    status = mongo_insert (node->conn, collection_name, bson_record, NULL);
  #else
    status = mongo_insert (node->conn, collection_name, bson_record);
  #endif

  if (status != MONGO_OK)
  {
    ERROR ( "write_mongodb plugin: error inserting record: %d", node->conn->err);
    if (node->conn->err != MONGO_BSON_INVALID)
      ERROR ("write_mongodb plugin: %s", node->conn->errstr);
    else
      ERROR ("write_mongodb plugin: Invalid BSON structure, error = %#x",
          (unsigned int) bson_record->err);

    /* Disconnect except on data errors. */
    if ((node->conn->err != MONGO_BSON_INVALID)
        && (node->conn->err != MONGO_BSON_NOT_FINISHED))
      mongo_destroy (node->conn);
  }

  pthread_mutex_unlock (&node->lock);

  /* free our resource as not to leak memory */
  bson_destroy (bson_record); /* matches bson_init() */
  bson_dealloc (bson_record); /* matches bson_alloc() */

  return (0);
}