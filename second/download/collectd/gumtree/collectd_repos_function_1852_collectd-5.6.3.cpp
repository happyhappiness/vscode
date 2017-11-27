static int mysql_read_wsrep_stats(mysql_database_t *db, MYSQL *con) {
  MYSQL_RES *res;
  MYSQL_ROW row;

  const char *query;
  struct {
    const char *key;
    const char *type;
    int ds_type;
  } metrics[] = {

      {"wsrep_apply_oooe", "operations", DS_TYPE_DERIVE},
      {"wsrep_apply_oool", "operations", DS_TYPE_DERIVE},
      {"wsrep_causal_reads", "operations", DS_TYPE_DERIVE},
      {"wsrep_commit_oooe", "operations", DS_TYPE_DERIVE},
      {"wsrep_commit_oool", "operations", DS_TYPE_DERIVE},
      {"wsrep_flow_control_recv", "operations", DS_TYPE_DERIVE},
      {"wsrep_flow_control_sent", "operations", DS_TYPE_DERIVE},
      {"wsrep_flow_control_paused", "operations", DS_TYPE_DERIVE},
      {"wsrep_local_bf_aborts", "operations", DS_TYPE_DERIVE},
      {"wsrep_local_cert_failures", "operations", DS_TYPE_DERIVE},
      {"wsrep_local_commits", "operations", DS_TYPE_DERIVE},
      {"wsrep_local_replays", "operations", DS_TYPE_DERIVE},
      {"wsrep_received", "operations", DS_TYPE_DERIVE},
      {"wsrep_replicated", "operations", DS_TYPE_DERIVE},

      {"wsrep_received_bytes", "total_bytes", DS_TYPE_DERIVE},
      {"wsrep_replicated_bytes", "total_bytes", DS_TYPE_DERIVE},

      {"wsrep_apply_window", "gauge", DS_TYPE_GAUGE},
      {"wsrep_commit_window", "gauge", DS_TYPE_GAUGE},

      {"wsrep_cluster_size", "gauge", DS_TYPE_GAUGE},
      {"wsrep_cert_deps_distance", "gauge", DS_TYPE_GAUGE},

      {"wsrep_local_recv_queue", "queue_length", DS_TYPE_GAUGE},
      {"wsrep_local_send_queue", "queue_length", DS_TYPE_GAUGE},

      {NULL, NULL, 0}

  };

  query = "SHOW GLOBAL STATUS LIKE 'wsrep_%'";

  res = exec_query(con, query);
  if (res == NULL)
    return (-1);

  row = mysql_fetch_row(res);
  if (row == NULL) {
    ERROR("mysql plugin: Failed to get wsrep statistics: "
          "`%s' did not return any rows.",
          query);
    mysql_free_result(res);
    return (-1);
  }

  while ((row = mysql_fetch_row(res))) {
    int i;
    char *key;
    unsigned long long val;

    key = row[0];
    val = atoll(row[1]);

    for (i = 0; metrics[i].key != NULL && strcmp(metrics[i].key, key) != 0; i++)
      ;

    if (metrics[i].key == NULL)
      continue;

    switch (metrics[i].ds_type) {
    case DS_TYPE_GAUGE:
      gauge_submit(metrics[i].type, key, (gauge_t)val, db);
      break;
    case DS_TYPE_DERIVE:
      derive_submit(metrics[i].type, key, (derive_t)val, db);
      break;
    }
  }

  mysql_free_result(res);
  return (0);
}