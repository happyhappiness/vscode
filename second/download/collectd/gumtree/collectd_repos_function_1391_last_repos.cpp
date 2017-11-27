static int wr_write(const data_set_t *ds, /* {{{ */
                    const value_list_t *vl, user_data_t *ud) {
  wr_node_t *node = ud->data;
  char ident[512];
  char key[512];
  char value[512] = {0};
  char time[24];
  size_t value_size;
  char *value_ptr;
  int status;
  redisReply *rr;

  status = FORMAT_VL(ident, sizeof(ident), vl);
  if (status != 0)
    return status;
  snprintf(key, sizeof(key), "%s%s",
           (node->prefix != NULL) ? node->prefix : REDIS_DEFAULT_PREFIX, ident);
  snprintf(time, sizeof(time), "%.9f", CDTIME_T_TO_DOUBLE(vl->time));

  value_size = sizeof(value);
  value_ptr = &value[0];
  status = format_values(value_ptr, value_size, ds, vl, node->store_rates);
  if (status != 0)
    return status;

  pthread_mutex_lock(&node->lock);

  if (node->conn == NULL) {
    node->conn =
        redisConnectWithTimeout((char *)node->host, node->port, node->timeout);
    if (node->conn == NULL) {
      ERROR("write_redis plugin: Connecting to host \"%s\" (port %i) failed: "
            "Unknown reason",
            (node->host != NULL) ? node->host : "localhost",
            (node->port != 0) ? node->port : 6379);
      pthread_mutex_unlock(&node->lock);
      return -1;
    } else if (node->conn->err) {
      ERROR(
          "write_redis plugin: Connecting to host \"%s\" (port %i) failed: %s",
          (node->host != NULL) ? node->host : "localhost",
          (node->port != 0) ? node->port : 6379, node->conn->errstr);
      pthread_mutex_unlock(&node->lock);
      return -1;
    }

    rr = redisCommand(node->conn, "SELECT %d", node->database);
    if (rr == NULL)
      WARNING("SELECT command error. database:%d message:%s", node->database,
              node->conn->errstr);
    else
      freeReplyObject(rr);
  }

  rr = redisCommand(node->conn, "ZADD %s %s %s", key, time, value);
  if (rr == NULL)
    WARNING("ZADD command error. key:%s message:%s", key, node->conn->errstr);
  else
    freeReplyObject(rr);

  if (node->max_set_size >= 0) {
    rr = redisCommand(node->conn, "ZREMRANGEBYRANK %s %d %d", key, 0,
                      (-1 * node->max_set_size) - 1);
    if (rr == NULL)
      WARNING("ZREMRANGEBYRANK command error. key:%s message:%s", key,
              node->conn->errstr);
    else
      freeReplyObject(rr);
  }

  if (node->max_set_duration > 0) {
    /*
     * remove element, scored less than 'current-max_set_duration'
     * '(%d' indicates 'less than' in redis CLI.
     */
    rr = redisCommand(node->conn, "ZREMRANGEBYSCORE %s -1 (%d", key,
                      (time - node->max_set_duration) + 1);
    if (rr == NULL)
      WARNING("ZREMRANGEBYSCORE command error. key:%s message:%s", key,
              node->conn->errstr);
    else
      freeReplyObject(rr);
  }

  /* TODO(octo): This is more overhead than necessary. Use the cache and
   * metadata to determine if it is a new metric and call SADD only once for
   * each metric. */
  rr = redisCommand(
      node->conn, "SADD %svalues %s",
      (node->prefix != NULL) ? node->prefix : REDIS_DEFAULT_PREFIX, ident);
  if (rr == NULL)
    WARNING("SADD command error. ident:%s message:%s", ident,
            node->conn->errstr);
  else
    freeReplyObject(rr);

  pthread_mutex_unlock(&node->lock);

  return 0;
}