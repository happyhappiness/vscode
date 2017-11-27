static MYSQL *getconnection (void)
{
	static MYSQL *con;
	static int    state;

	static int wait_for = 0;
	static int wait_increase = 60;

	if (state != 0)
	{
		int err;
		if ((err = mysql_ping (con)) != 0)
		{
			WARNING ("mysql_ping failed: %s", mysql_error (con));
			state = 0;
		}
		else
		{
			state = 1;
			return (con);
		}
	}

	if (wait_for > 0)
	{
		wait_for -= interval_g;
		return (NULL);
	}

	wait_for = wait_increase;
	wait_increase *= 2;
	if (wait_increase > 86400)
		wait_increase = 86400;

	if ((con = mysql_init (con)) == NULL)
	{
		ERROR ("mysql_init failed: %s", mysql_error (con));
		state = 0;
		return (NULL);
	}

	if (mysql_real_connect (con, host, user, pass, db, 0, NULL, 0) == NULL)
	{
		ERROR ("mysql_real_connect failed: %s", mysql_error (con));
		state = 0;
		return (NULL);
	}
	else
	{
		state = 1;
		wait_for = 0;
		wait_increase = 60;
		return (con);
	}
}