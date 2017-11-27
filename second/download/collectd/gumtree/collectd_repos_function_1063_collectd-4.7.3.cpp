static int mysql_read_master_stats (mysql_database_t *db, MYSQL *con)
{
	MYSQL_RES *res;
	MYSQL_ROW  row;

	char *query;
	int   field_num;
	unsigned long long position;

	query = "SHOW MASTER STATUS";

	res = exec_query (con, query);
	if (res == NULL)
		return (-1);

	row = mysql_fetch_row (res);
	if (row == NULL)
	{
		ERROR ("mysql plugin: Failed to get master statistics: "
				"`%s' did not return any rows.", query);
		return (-1);
	}

	field_num = mysql_num_fields (res);
	if (field_num < 2)
	{
		ERROR ("mysql plugin: Failed to get master statistics: "
				"`%s' returned less than two columns.", query);
		return (-1);
	}

	position = atoll (row[1]);
	counter_submit ("mysql_log_position", "master-bin", position, db);

	row = mysql_fetch_row (res);
	if (row != NULL)
		WARNING ("mysql plugin: `%s' returned more than one row - "
				"ignoring further results.", query);

	mysql_free_result (res);

	return (0);
}