static int mysql_read (user_data_t *ud)
{
	mysql_database_t *db;
	MYSQL     *con;
	MYSQL_RES *res;
	MYSQL_ROW  row;
	char      *query;

	unsigned long long qcache_hits          = 0ULL;
	unsigned long long qcache_inserts       = 0ULL;
	unsigned long long qcache_not_cached    = 0ULL;
	unsigned long long qcache_lowmem_prunes = 0ULL;
	int qcache_queries_in_cache = -1;

	int threads_running   = -1;
	int threads_connected = -1;
	int threads_cached    = -1;
	unsigned long long threads_created = 0ULL;

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
				qcache_hits = val;
			else if (strcmp (key, "Qcache_inserts") == 0)
				qcache_inserts = val;
			else if (strcmp (key, "Qcache_not_cached") == 0)
				qcache_not_cached = val;
			else if (strcmp (key, "Qcache_lowmem_prunes") == 0)
				qcache_lowmem_prunes = val;
			else if (strcmp (key, "Qcache_queries_in_cache") == 0)
				qcache_queries_in_cache = (int) val;
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
				threads_running = (int) val;
			else if (strcmp (key, "Threads_connected") == 0)
				threads_connected = (int) val;
			else if (strcmp (key, "Threads_cached") == 0)
				threads_cached = (int) val;
			else if (strcmp (key, "Threads_created") == 0)
				threads_created = val;
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

	if ((qcache_hits != 0ULL)
			|| (qcache_inserts != 0ULL)
			|| (qcache_not_cached != 0ULL)
			|| (qcache_lowmem_prunes != 0ULL))
		qcache_submit (qcache_hits, qcache_inserts, qcache_not_cached,
			       qcache_lowmem_prunes, qcache_queries_in_cache, db);

	if (threads_created != 0ULL)
		threads_submit (threads_running, threads_connected,
				threads_cached, threads_created, db);

	traffic_submit  (traffic_incoming, traffic_outgoing, db);

	if (db->master_stats)
		mysql_read_master_stats (db, con);

	if ((db->slave_stats) || (db->slave_notif))
		mysql_read_slave_stats (db, con);

	return (0);
}