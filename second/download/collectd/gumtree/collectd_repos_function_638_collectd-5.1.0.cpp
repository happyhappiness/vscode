static int redis_read (void) /* {{{ */
{
  redis_node_t *rn;

  for (rn = nodes_head; rn != NULL; rn = rn->next)
  {
    REDIS rh;
    REDIS_INFO info;

    int status;

    DEBUG ("redis plugin: querying info from node `%s' (%s:%d).", rn->name, rn->host, rn->port);

    rh = credis_connect (rn->host, rn->port, rn->timeout);
    if (rh == NULL)
    {
      ERROR ("redis plugin: unable to connect to node `%s' (%s:%d).", rn->name, rn->host, rn->port);
      continue;
    }

    memset (&info, 0, sizeof (info));
    status = credis_info (rh, &info);
    if (status != 0)
    {
      WARNING ("redis plugin: unable to get info from node `%s'.", rn->name);
      credis_close (rh);
      continue;
    }

    /* typedef struct _cr_info {
     *   char redis_version[CREDIS_VERSION_STRING_SIZE];
     *   int bgsave_in_progress;
     *   int connected_clients;
     *   int connected_slaves;
     *   unsigned int used_memory;
     *   long long changes_since_last_save;
     *   int last_save_time;
     *   long long total_connections_received;
     *   long long total_commands_processed;
     *   int uptime_in_seconds;
     *   int uptime_in_days;
     *   int role;
     * } REDIS_INFO; */

    DEBUG ("redis plugin: received info from node `%s': connected_clients = %d; "
        "connected_slaves = %d; used_memory = %lu; changes_since_last_save = %lld; "
        "bgsave_in_progress = %d; total_connections_received = %lld; "
        "total_commands_processed = %lld; uptime_in_seconds = %ld", rn->name,
        info.connected_clients, info.connected_slaves, info.used_memory,
        info.changes_since_last_save, info.bgsave_in_progress,
        info.total_connections_received, info.total_commands_processed,
        info.uptime_in_seconds);

    redis_submit_g (rn->name, "current_connections", "clients", info.connected_clients);
    redis_submit_g (rn->name, "current_connections", "slaves", info.connected_slaves);
    redis_submit_g (rn->name, "memory", "used", info.used_memory);
    redis_submit_g (rn->name, "volatile_changes", NULL, info.changes_since_last_save);
    redis_submit_d (rn->name, "total_connections", NULL, info.total_connections_received);
    redis_submit_d (rn->name, "total_operations", NULL, info.total_commands_processed);

    credis_close (rh);
  }

  return 0;
}