static int mysql_read_slave_stats (mysql_database_t *db, MYSQL *con)
{
	MYSQL_RES *res;
	MYSQL_ROW  row;

	char *query;
	int   field_num;

	/* WTF? libmysqlclient does not seem to provide any means to
	 * translate a column name to a column index ... :-/ */
	const int READ_MASTER_LOG_POS_IDX   = 6;
	const int SLAVE_IO_RUNNING_IDX      = 10;
	const int SLAVE_SQL_RUNNING_IDX     = 11;
	const int EXEC_MASTER_LOG_POS_IDX   = 21;
	const int SECONDS_BEHIND_MASTER_IDX = 32;

	query = "SHOW SLAVE STATUS";

	res = exec_query (con, query);
	if (res == NULL)
		return (-1);

	row = mysql_fetch_row (res);
	if (row == NULL)
	{
		ERROR ("mysql plugin: Failed to get slave statistics: "
				"`%s' did not return any rows.", query);
		mysql_free_result (res);
		return (-1);
	}

	field_num = mysql_num_fields (res);
	if (field_num < 33)
	{
		ERROR ("mysql plugin: Failed to get slave statistics: "
				"`%s' returned less than 33 columns.", query);
		mysql_free_result (res);
		return (-1);
	}

	if (db->slave_stats)
	{
		unsigned long long counter;
		double gauge;

		counter = atoll (row[READ_MASTER_LOG_POS_IDX]);
		counter_submit ("mysql_log_position", "slave-read", counter, db);

		counter = atoll (row[EXEC_MASTER_LOG_POS_IDX]);
		counter_submit ("mysql_log_position", "slave-exec", counter, db);

		if (row[SECONDS_BEHIND_MASTER_IDX] != NULL)
		{
			gauge = atof (row[SECONDS_BEHIND_MASTER_IDX]);
			gauge_submit ("time_offset", NULL, gauge, db);
		}
	}

	if (db->slave_notif)
	{
		notification_t n = { 0, time (NULL), "", "",
			"mysql", "", "time_offset", "", NULL };

		char *io, *sql;

		io  = row[SLAVE_IO_RUNNING_IDX];
		sql = row[SLAVE_SQL_RUNNING_IDX];

		set_host (db, n.host, sizeof (n.host));
		set_plugin_instance (db,
				n.plugin_instance, sizeof (n.plugin_instance));

		if (((io == NULL) || (strcasecmp (io, "yes") != 0))
				&& (db->slave_io_running))
		{
			n.severity = NOTIF_WARNING;
			ssnprintf (n.message, sizeof (n.message),
					"slave I/O thread not started or not connected to master");
			plugin_dispatch_notification (&n);
			db->slave_io_running = 0;
		}
		else if (((io != NULL) && (strcasecmp (io, "yes") == 0))
				&& (! db->slave_io_running))
		{
			n.severity = NOTIF_OKAY;
			ssnprintf (n.message, sizeof (n.message),
					"slave I/O thread started and connected to master");
			plugin_dispatch_notification (&n);
			db->slave_io_running = 1;
		}

		if (((sql == NULL) || (strcasecmp (sql, "yes") != 0))
				&& (db->slave_sql_running))
		{
			n.severity = NOTIF_WARNING;
			ssnprintf (n.message, sizeof (n.message),
					"slave SQL thread not started");
			plugin_dispatch_notification (&n);
			db->slave_sql_running = 0;
		}
		else if (((sql != NULL) && (strcasecmp (sql, "yes") == 0))
				&& (! db->slave_sql_running))
		{
			n.severity = NOTIF_OKAY;
			ssnprintf (n.message, sizeof (n.message),
					"slave SQL thread started");
			plugin_dispatch_notification (&n);
			db->slave_sql_running = 0;
		}
	}

	row = mysql_fetch_row (res);
	if (row != NULL)
		WARNING ("mysql plugin: `%s' returned more than one row - "
				"ignoring further results.", query);

	mysql_free_result (res);

	return (0);
}