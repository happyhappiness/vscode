static int apcups_read (void)
{
	struct apc_detail_s apcups_detail;
	int status;

	apcups_detail.linev    =   -1.0;
	apcups_detail.outputv  =   -1.0;
	apcups_detail.battv    =   -1.0;
	apcups_detail.loadpct  =   -1.0;
	apcups_detail.bcharge  =   -1.0;
	apcups_detail.timeleft =   -1.0;
	apcups_detail.itemp    = -300.0;
	apcups_detail.linefreq =   -1.0;

	status = apc_query_server (conf_host == NULL
			? APCUPS_DEFAULT_HOST
			: conf_host,
			conf_port, &apcups_detail);

	/*
	 * if we did not connect then do not bother submitting
	 * zeros. We want rrd files to have NAN.
	 */
	if (status != 0)
	{
		DEBUG ("apc_query_server (%s, %i) = %i",
				conf_host == NULL
				? APCUPS_DEFAULT_HOST
				: conf_host,
				conf_port, status);
		return (-1);
	}

	apc_submit (&apcups_detail);

	return (0);
}