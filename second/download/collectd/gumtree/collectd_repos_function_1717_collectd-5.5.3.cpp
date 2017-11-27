static int mysql_read_innodb_stats (mysql_database_t *db, MYSQL *con)
{
	MYSQL_RES *res;
	MYSQL_ROW  row;

	char *query;
    struct {
        char *key;
        char *type;
        int ds_type;
    } metrics[] = {
        { "metadata_mem_pool_size",         "bytes",        DS_TYPE_GAUGE },
        { "lock_deadlocks",                 "mysql_locks",  DS_TYPE_DERIVE },
        { "lock_timeouts",                  "mysql_locks",  DS_TYPE_DERIVE },
        { "lock_row_lock_current_waits",    "mysql_locks",  DS_TYPE_DERIVE },
        { "buffer_pool_size",               "bytes",        DS_TYPE_GAUGE },

        { "buffer_pool_reads",              "operations",   DS_TYPE_DERIVE },
        { "buffer_pool_read_requests",      "operations",   DS_TYPE_DERIVE },
        { "buffer_pool_write_requests",     "operations",   DS_TYPE_DERIVE },
        { "buffer_pool_wait_free",          "operations",   DS_TYPE_DERIVE },
        { "buffer_pool_read_ahead",         "operations",   DS_TYPE_DERIVE },
        { "buffer_pool_read_ahead_evicted", "operations",   DS_TYPE_DERIVE },

        { "buffer_pool_pages_total",        "gauge",        DS_TYPE_GAUGE },
        { "buffer_pool_pages_misc",         "gauge",        DS_TYPE_GAUGE },
        { "buffer_pool_pages_data",         "gauge",        DS_TYPE_GAUGE },
        { "buffer_pool_bytes_data",         "gauge",        DS_TYPE_GAUGE },
        { "buffer_pool_pages_dirty",        "gauge",        DS_TYPE_GAUGE },
        { "buffer_pool_bytes_dirty",        "gauge",        DS_TYPE_GAUGE },
        { "buffer_pool_pages_free",         "gauge",        DS_TYPE_GAUGE },

        { "buffer_pages_created",           "operations",   DS_TYPE_DERIVE },
        { "buffer_pages_written",           "operations",   DS_TYPE_DERIVE },
        { "buffer_pages_read",              "operations",   DS_TYPE_DERIVE },
        { "buffer_data_reads",              "operations",   DS_TYPE_DERIVE },
        { "buffer_data_written",            "operations",   DS_TYPE_DERIVE },

        { "os_data_reads",                  "operations",   DS_TYPE_DERIVE },
        { "os_data_writes",                 "operations",   DS_TYPE_DERIVE },
        { "os_data_fsyncs",                 "operations",   DS_TYPE_DERIVE },
        { "os_log_bytes_written",           "operations",   DS_TYPE_DERIVE },
        { "os_log_fsyncs",                  "operations",   DS_TYPE_DERIVE },
        { "os_log_pending_fsyncs",          "operations",   DS_TYPE_DERIVE },
        { "os_log_pending_writes",          "operations",   DS_TYPE_DERIVE },

        { "trx_rseg_history_len",           "gauge",        DS_TYPE_GAUGE },

        { "log_waits",                      "operations",   DS_TYPE_DERIVE },
        { "log_write_requests",             "operations",   DS_TYPE_DERIVE },
        { "log_writes",                     "operations",   DS_TYPE_DERIVE },
        { "adaptive_hash_searches",         "operations",   DS_TYPE_DERIVE },

        { "file_num_open_files",            "gauge",        DS_TYPE_GAUGE },

        { "ibuf_merges_insert",             "operations",   DS_TYPE_DERIVE },
        { "ibuf_merges_delete_mark",        "operations",   DS_TYPE_DERIVE },
        { "ibuf_merges_delete",             "operations",   DS_TYPE_DERIVE },
        { "ibuf_merges_discard_insert",     "operations",   DS_TYPE_DERIVE },
        { "ibuf_merges_discard_delete_mark","operations",   DS_TYPE_DERIVE },
        { "ibuf_merges_discard_delete",     "operations",   DS_TYPE_DERIVE },
        { "ibuf_merges_discard_merges",     "operations",   DS_TYPE_DERIVE },
        { "ibuf_size",                      "bytes",        DS_TYPE_GAUGE },

        { "innodb_activity_count",          "gauge",        DS_TYPE_GAUGE },
        { "innodb_dblwr_writes",            "operations",   DS_TYPE_DERIVE },
        { "innodb_dblwr_pages_written",     "operations",   DS_TYPE_DERIVE },
        { "innodb_dblwr_page_size",         "gauge",        DS_TYPE_GAUGE },

        { "innodb_rwlock_s_spin_waits",     "operations",   DS_TYPE_DERIVE },
        { "innodb_rwlock_x_spin_waits",     "operations",   DS_TYPE_DERIVE },
        { "innodb_rwlock_s_spin_rounds",    "operations",   DS_TYPE_DERIVE },
        { "innodb_rwlock_x_spin_rounds",    "operations",   DS_TYPE_DERIVE },
        { "innodb_rwlock_s_os_waits",       "operations",   DS_TYPE_DERIVE },
        { "innodb_rwlock_x_os_waits",       "operations",   DS_TYPE_DERIVE },

        { "dml_reads",                      "operations",   DS_TYPE_DERIVE },
        { "dml_inserts",                    "operations",   DS_TYPE_DERIVE },
        { "dml_deletes",                    "operations",   DS_TYPE_DERIVE },
        { "dml_updates",                    "operations",   DS_TYPE_DERIVE },

        { NULL,                     NULL,           0}
    };

	query = "SELECT name, count, type FROM information_schema.innodb_metrics WHERE status = 'enabled'";

	res = exec_query (con, query);
	if (res == NULL)
		return (-1);

	while ((row = mysql_fetch_row (res)))
	{
        int i;
		char *key;
		unsigned long long val;

		key = row[0];
		val = atoll (row[1]);

        for (i = 0;
             metrics[i].key != NULL && strcmp(metrics[i].key, key) != 0;
             i++)
            ;

        if (metrics[i].key == NULL)
            continue;

        switch (metrics[i].ds_type) {
        case DS_TYPE_COUNTER:
            counter_submit(metrics[i].type, key, (counter_t)val, db);
            break;
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