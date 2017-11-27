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

	if ((ud == NULL) || (ud->data == NULL))
	{
		ERROR ("mysql plugin: mysql_database_read: Invalid user data.");
		return (-1);
	}

	db = (mysql_database_t *) ud->data;

	/* An error message will have been printed in this case */
	if ((con = getconnection (db)) == NULL)
		return (-1);

	query = "SHOW STATUS";
	if (mysql_get_server_version (con) >= 50002)
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

	if (db->master_stats)
		mysql_read_master_stats (db, con);

	if ((db->slave_stats) || (db->slave_notif))
		mysql_read_slave_stats (db, con);

	return (0);
}