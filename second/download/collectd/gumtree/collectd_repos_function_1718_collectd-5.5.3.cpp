static int mysql_read (user_data_t *ud)
{
	mysql_database_t *db;
	MYSQL     *con;
	MYSQL_RES *res;
	MYSQL_ROW  row;
	char      *query;

	derive_t qcache_hits          = 0;
	derive_t qcache_inserts       = 0;
	derive_t qcache_not_cached    = 0;
	derive_t qcache_lowmem_prunes = 0;
	gauge_t qcache_queries_in_cache = NAN;

	gauge_t threads_running   = NAN;
	gauge_t threads_connected = NAN;
	gauge_t threads_cached    = NAN;
	derive_t threads_created = 0;

	unsigned long long traffic_incoming = 0ULL;
	unsigned long long traffic_outgoing = 0ULL;
    unsigned long mysql_version = 0ULL;

	if ((ud == NULL) || (ud->data == NULL))
	{
		ERROR ("mysql plugin: mysql_database_read: Invalid user data.");
		return (-1);
	}

	db = (mysql_database_t *) ud->data;

	/* An error message will have been printed in this case */
	if ((con = getconnection (db)) == NULL)
		return (-1);

  mysql_version = mysql_get_server_version(con);

	query = "SHOW STATUS";
	if (mysql_version >= 50002)
		query = "SHOW GLOBAL STATUS";

	res = exec_query (con, query);
	if (res == NULL)
		return (-1);

	while ((row = mysql_fetch_row (res)))
	{
		char *key;
		unsigned long long val;

		key = row[0];
		val = atoll (row[1]);

		if (strncmp (key, "Com_", 
			          strlen ("Com_")) == 0)
		{
			if (val == 0ULL)
				continue;

			/* Ignore `prepared statements' */
			if (strncmp (key, "Com_stmt_", strlen ("Com_stmt_")) != 0)
				counter_submit ("mysql_commands", 
						key + strlen ("Com_"), 
						val, db);
		}
		else if (strncmp (key, "Handler_", 
				        strlen ("Handler_")) == 0)
		{
			if (val == 0ULL)
				continue;

			counter_submit ("mysql_handler", 
					key + strlen ("Handler_"), 
					val, db);
		}
		else if (strncmp (key, "Qcache_",
       				        strlen ("Qcache_")) == 0)
		{
			if (strcmp (key, "Qcache_hits") == 0)
				qcache_hits = (derive_t) val;
			else if (strcmp (key, "Qcache_inserts") == 0)
				qcache_inserts = (derive_t) val;
			else if (strcmp (key, "Qcache_not_cached") == 0)
				qcache_not_cached = (derive_t) val;
			else if (strcmp (key, "Qcache_lowmem_prunes") == 0)
				qcache_lowmem_prunes = (derive_t) val;
			else if (strcmp (key, "Qcache_queries_in_cache") == 0)
				qcache_queries_in_cache = (gauge_t) val;
		}
		else if (strncmp (key, "Bytes_", 
				        strlen ("Bytes_")) == 0)
		{
			if (strcmp (key, "Bytes_received") == 0)
				traffic_incoming += val;
			else if (strcmp (key, "Bytes_sent") == 0)
				traffic_outgoing += val;
		}
		else if (strncmp (key, "Threads_", 
       				        strlen ("Threads_")) == 0)
		{
			if (strcmp (key, "Threads_running") == 0)
				threads_running = (gauge_t) val;
			else if (strcmp (key, "Threads_connected") == 0)
				threads_connected = (gauge_t) val;
			else if (strcmp (key, "Threads_cached") == 0)
				threads_cached = (gauge_t) val;
			else if (strcmp (key, "Threads_created") == 0)
				threads_created = (derive_t) val;
		}
		else if (strncmp (key, "Table_locks_",
					strlen ("Table_locks_")) == 0)
		{
			counter_submit ("mysql_locks",
					key + strlen ("Table_locks_"),
					val, db);
		}
		else if (db->innodb_stats && strncmp (key, "Innodb_", strlen ("Innodb_")) == 0)
		{
			/* buffer pool */
			if (strcmp (key, "Innodb_buffer_pool_pages_data") == 0)
				gauge_submit ("mysql_bpool_pages", "data", val, db);
			else if (strcmp (key, "Innodb_buffer_pool_pages_dirty") == 0)
				gauge_submit ("mysql_bpool_pages", "dirty", val, db);
			else if (strcmp (key, "Innodb_buffer_pool_pages_flushed") == 0)
				counter_submit ("mysql_bpool_counters", "pages_flushed", val, db);
			else if (strcmp (key, "Innodb_buffer_pool_pages_free") == 0)
				gauge_submit ("mysql_bpool_pages", "free", val, db);
			else if (strcmp (key, "Innodb_buffer_pool_pages_misc") == 0)
				gauge_submit ("mysql_bpool_pages", "misc", val, db);
			else if (strcmp (key, "Innodb_buffer_pool_pages_total") == 0)
				gauge_submit ("mysql_bpool_pages", "total", val, db);
			else if (strcmp (key, "Innodb_buffer_pool_read_ahead_rnd") == 0)
				counter_submit ("mysql_bpool_counters", "read_ahead_rnd", val, db);
			else if (strcmp (key, "Innodb_buffer_pool_read_ahead") == 0)
				counter_submit ("mysql_bpool_counters", "read_ahead", val, db);
			else if (strcmp (key, "Innodb_buffer_pool_read_ahead_evicted") == 0)
				counter_submit ("mysql_bpool_counters", "read_ahead_evicted", val, db);
			else if (strcmp (key, "Innodb_buffer_pool_read_requests") == 0)
				counter_submit ("mysql_bpool_counters", "read_requests", val, db);
			else if (strcmp (key, "Innodb_buffer_pool_reads") == 0)
				counter_submit ("mysql_bpool_counters", "reads", val, db);
			else if (strcmp (key, "Innodb_buffer_pool_write_requests") == 0)
				counter_submit ("mysql_bpool_counters", "write_requests", val, db);
			else if (strcmp (key, "Innodb_buffer_pool_bytes_data") == 0)
				gauge_submit ("mysql_bpool_bytes", "data", val, db);
			else if (strcmp (key, "Innodb_buffer_pool_bytes_dirty") == 0)
				gauge_submit ("mysql_bpool_bytes", "dirty", val, db);

			/* data */
			if (strcmp (key, "Innodb_data_fsyncs") == 0)
				counter_submit ("mysql_innodb_data", "fsyncs", val, db);
			else if (strcmp (key, "Innodb_data_read") == 0)
				counter_submit ("mysql_innodb_data", "read", val, db);
			else if (strcmp (key, "Innodb_data_reads") == 0)
				counter_submit ("mysql_innodb_data", "reads", val, db);
			else if (strcmp (key, "Innodb_data_writes") == 0)
				counter_submit ("mysql_innodb_data", "writes", val, db);
			else if (strcmp (key, "Innodb_data_written") == 0)
				counter_submit ("mysql_innodb_data", "written", val, db);

			/* double write */
			else if (strcmp (key, "Innodb_dblwr_writes") == 0)
				counter_submit ("mysql_innodb_dblwr", "writes", val, db);
			else if (strcmp (key, "Innodb_dblwr_pages_written") == 0)
				counter_submit ("mysql_innodb_dblwr", "written", val, db);

			/* log */
			else if (strcmp (key, "Innodb_log_waits") == 0)
				counter_submit ("mysql_innodb_log", "waits", val, db);
			else if (strcmp (key, "Innodb_log_write_requests") == 0)
				counter_submit ("mysql_innodb_log", "write_requests", val, db);
			else if (strcmp (key, "Innodb_log_writes") == 0)
				counter_submit ("mysql_innodb_log", "writes", val, db);
			else if (strcmp (key, "Innodb_os_log_fsyncs") == 0)
				counter_submit ("mysql_innodb_log", "fsyncs", val, db);
			else if (strcmp (key, "Innodb_os_log_written") == 0)
				counter_submit ("mysql_innodb_log", "written", val, db);

			/* pages */
			else if (strcmp (key, "Innodb_pages_created") == 0)
				counter_submit ("mysql_innodb_pages", "created", val, db);
			else if (strcmp (key, "Innodb_pages_read") == 0)
				counter_submit ("mysql_innodb_pages", "read", val, db);
			else if (strcmp (key, "Innodb_pages_written") == 0)
				counter_submit ("mysql_innodb_pages", "written", val, db);

			/* row lock */
			else if (strcmp (key, "Innodb_row_lock_time") == 0)
				counter_submit ("mysql_innodb_row_lock", "time", val, db);
			else if (strcmp (key, "Innodb_row_lock_waits") == 0)
				counter_submit ("mysql_innodb_row_lock", "waits", val, db);

			/* rows */
			else if (strcmp (key, "Innodb_rows_deleted") == 0)
				counter_submit ("mysql_innodb_rows", "deleted", val, db);
			else if (strcmp (key, "Innodb_rows_inserted") == 0)
				counter_submit ("mysql_innodb_rows", "inserted", val, db);
			else if (strcmp (key, "Innodb_rows_read") == 0)
				counter_submit ("mysql_innodb_rows", "read", val, db);
			else if (strcmp (key, "Innodb_rows_updated") == 0)
				counter_submit ("mysql_innodb_rows", "updated", val, db);
		}
		else if (strncmp (key, "Select_", strlen ("Select_")) == 0)
		{
			counter_submit ("mysql_select", key + strlen ("Select_"),
					val, db);
		}
		else if (strncmp (key, "Sort_", strlen ("Sort_")) == 0)
		{
			counter_submit ("mysql_sort", key + strlen ("Sort_"),
					val, db);
		}
	}
	mysql_free_result (res); res = NULL;

	if ((qcache_hits != 0)
			|| (qcache_inserts != 0)
			|| (qcache_not_cached != 0)
			|| (qcache_lowmem_prunes != 0))
	{
		derive_submit ("cache_result", "qcache-hits",
				qcache_hits, db);
		derive_submit ("cache_result", "qcache-inserts",
				qcache_inserts, db);
		derive_submit ("cache_result", "qcache-not_cached",
				qcache_not_cached, db);
		derive_submit ("cache_result", "qcache-prunes",
				qcache_lowmem_prunes, db);

		gauge_submit ("cache_size", "qcache",
				qcache_queries_in_cache, db);
	}

	if (threads_created != 0)
	{
		gauge_submit ("threads", "running",
				threads_running, db);
		gauge_submit ("threads", "connected",
				threads_connected, db);
		gauge_submit ("threads", "cached",
				threads_cached, db);

		derive_submit ("total_threads", "created",
				threads_created, db);
	}

	traffic_submit  (traffic_incoming, traffic_outgoing, db);

	if (mysql_version >= 50600 && db->innodb_stats)
        mysql_read_innodb_stats (db, con);

	if (db->master_stats)
		mysql_read_master_stats (db, con);

	if ((db->slave_stats) || (db->slave_notif))
		mysql_read_slave_stats (db, con);

	return (0);
}