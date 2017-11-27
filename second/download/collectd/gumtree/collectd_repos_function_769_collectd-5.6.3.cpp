static int redis_read(void) /* {{{ */
{
  for (redis_node_t *rn = nodes_head; rn != NULL; rn = rn->next) {
    redisContext *rh;
    redisReply *rr;

    DEBUG("redis plugin: querying info from node `%s' (%s:%d).", rn->name,
          rn->host, rn->port);

    rh = redisConnectWithTimeout((char *)rn->host, rn->port, rn->timeout);
    if (rh == NULL) {
      ERROR("redis plugin: unable to connect to node `%s' (%s:%d).", rn->name,
            rn->host, rn->port);
      continue;
    }

    if (strlen(rn->passwd) > 0) {
      DEBUG("redis plugin: authenticating node `%s' passwd(%s).", rn->name,
            rn->passwd);

      if ((rr = redisCommand(rh, "AUTH %s", rn->passwd)) == NULL) {
        WARNING("redis plugin: unable to authenticate on node `%s'.", rn->name);
        goto redis_fail;
      }

      if (rr->type != REDIS_REPLY_STATUS) {
        WARNING("redis plugin: invalid authentication on node `%s'.", rn->name);
        goto redis_fail;
      }

      freeReplyObject(rr);
    }

    if ((rr = redisCommand(rh, "INFO")) == NULL) {
      WARNING("redis plugin: unable to get info from node `%s'.", rn->name);
      goto redis_fail;
    }

    redis_handle_info(rn->name, rr->str, "uptime", NULL, "uptime_in_seconds",
                      DS_TYPE_GAUGE);
    redis_handle_info(rn->name, rr->str, "current_connections", "clients",
                      "connected_clients", DS_TYPE_GAUGE);
    redis_handle_info(rn->name, rr->str, "blocked_clients", NULL,
                      "blocked_clients", DS_TYPE_GAUGE);
    redis_handle_info(rn->name, rr->str, "memory", NULL, "used_memory",
                      DS_TYPE_GAUGE);
    redis_handle_info(rn->name, rr->str, "memory_lua", NULL, "used_memory_lua",
                      DS_TYPE_GAUGE);
    /* changes_since_last_save: Deprecated in redis version 2.6 and above */
    redis_handle_info(rn->name, rr->str, "volatile_changes", NULL,
                      "changes_since_last_save", DS_TYPE_GAUGE);
    redis_handle_info(rn->name, rr->str, "total_connections", NULL,
                      "total_connections_received", DS_TYPE_DERIVE);
    redis_handle_info(rn->name, rr->str, "total_operations", NULL,
                      "total_commands_processed", DS_TYPE_DERIVE);
    redis_handle_info(rn->name, rr->str, "operations_per_second", NULL,
                      "instantaneous_ops_per_sec", DS_TYPE_GAUGE);
    redis_handle_info(rn->name, rr->str, "expired_keys", NULL, "expired_keys",
                      DS_TYPE_DERIVE);
    redis_handle_info(rn->name, rr->str, "evicted_keys", NULL, "evicted_keys",
                      DS_TYPE_DERIVE);
    redis_handle_info(rn->name, rr->str, "pubsub", "channels",
                      "pubsub_channels", DS_TYPE_GAUGE);
    redis_handle_info(rn->name, rr->str, "pubsub", "patterns",
                      "pubsub_patterns", DS_TYPE_GAUGE);
    redis_handle_info(rn->name, rr->str, "current_connections", "slaves",
                      "connected_slaves", DS_TYPE_GAUGE);
    redis_handle_info(rn->name, rr->str, "cache_result", "hits",
                      "keyspace_hits", DS_TYPE_DERIVE);
    redis_handle_info(rn->name, rr->str, "cache_result", "misses",
                      "keyspace_misses", DS_TYPE_DERIVE);
    redis_handle_info(rn->name, rr->str, "total_bytes", "input",
                      "total_net_input_bytes", DS_TYPE_DERIVE);
    redis_handle_info(rn->name, rr->str, "total_bytes", "output",
                      "total_net_output_bytes", DS_TYPE_DERIVE);

    for (redis_query_t *rq = rn->queries; rq != NULL; rq = rq->next)
      redis_handle_query(rh, rn, rq);

  redis_fail:
    if (rr != NULL)
      freeReplyObject(rr);
    redisFree(rh);
  }

  return 0;
}