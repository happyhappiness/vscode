static int tss2_read_vserver (vserver_list_t *vserver)
{
	/*
	 * Poll information for the given vserver and submit it to collect.
	 * If vserver is NULL the global server information will be queried.
	 */
	int status;

	gauge_t users = NAN;
	gauge_t channels = NAN;
	gauge_t servers = NAN;
	counter_t rx_octets = 0;
	counter_t tx_octets = 0;
	counter_t rx_packets = 0;
	counter_t tx_packets = 0;
	gauge_t packet_loss = NAN;
	int valid = 0;

	char plugin_instance[DATA_MAX_NAME_LEN];

	FILE *read_fh;
	FILE *write_fh;

	/* Get the send/receive sockets */
	status = tss2_get_socket (&read_fh, &write_fh);
	if (status != 0)
	{
		ERROR ("teamspeak2 plugin: tss2_get_socket failed.");
		return (-1);
	}

	if (vserver == NULL)
	{
		/* Request global information */
		memset (plugin_instance, 0, sizeof (plugin_instance));

		status = tss2_send_request (write_fh, "gi\r\n");
	}
	else
	{
		/* Request server information */
		snprintf (plugin_instance, sizeof (plugin_instance), "vserver%i",
				vserver->port);
		plugin_instance[sizeof (plugin_instance) - 1] = 0;

		/* Select the server */
		status = tss2_select_vserver (read_fh, write_fh, vserver);
		if (status != 0)
			return (status);

		status = tss2_send_request (write_fh, "si\r\n");
	}

	if (status != 0)
	{
		ERROR ("teamspeak2 plugin: tss2_send_request failed.");
		return (-1);
	}

	/* Loop until break */
	while (42)
	{
		char buffer[4096];
		char *key;
		char *value;
		char *endptr = NULL;
		
		/* Read one line of the server's answer */
		status = tss2_receive_line (read_fh, buffer, sizeof (buffer));
		if (status != 0)
		{
			/* Set to NULL just to make sure noone uses these FHs anymore. */
			read_fh = NULL;
			write_fh = NULL;
			ERROR ("teamspeak2 plugin: tss2_receive_line failed.");
			break;
		}

		if (strncasecmp ("ERROR", buffer, 5) == 0)
		{
			ERROR ("teamspeak2 plugin: Server returned an error: %s",
					buffer);
			break;
		}
		else if (strncasecmp ("OK", buffer, 2) == 0)
		{
			break;
		}

		/* Split line into key and value */
		key = strchr (buffer, '_');
		if (key == NULL)
		{
			DEBUG ("teamspeak2 plugin: Cannot parse line: %s", buffer);
			continue;
		}
		key++;

		/* Evaluate assignment */
		value = strchr (key, '=');
		if (value == NULL)
		{
			DEBUG ("teamspeak2 plugin: Cannot parse line: %s", buffer);
			continue;
		}
		*value = 0;
		value++;

		/* Check for known key and save the given value */
		/* global info: users_online,
		 * server info: currentusers. */
		if ((strcmp ("currentusers", key) == 0)
				|| (strcmp ("users_online", key) == 0))
		{
			users = strtod (value, &endptr);
			if (value != endptr)
				valid |= 0x01;
		}
		/* global info: channels,
		 * server info: currentchannels. */
		else if ((strcmp ("currentchannels", key) == 0)
				|| (strcmp ("channels", key) == 0))
		{
			channels = strtod (value, &endptr);
			if (value != endptr)
				valid |= 0x40;
		}
		/* global only */
		else if (strcmp ("servers", key) == 0)
		{
			servers = strtod (value, &endptr);
			if (value != endptr)
				valid |= 0x80;
		}
		else if (strcmp ("bytesreceived", key) == 0)
		{
			rx_octets = strtoll (value, &endptr, 0);
			if (value != endptr)
				valid |= 0x02;
		}
		else if (strcmp ("bytessend", key) == 0)
		{
			tx_octets = strtoll (value, &endptr, 0);
			if (value != endptr)
				valid |= 0x04;
		}
		else if (strcmp ("packetsreceived", key) == 0)
		{
			rx_packets = strtoll (value, &endptr, 0);
			if (value != endptr)
				valid |= 0x08;
		}
		else if (strcmp ("packetssend", key) == 0)
		{
			tx_packets = strtoll (value, &endptr, 0);
			if (value != endptr)
				valid |= 0x10;
		}
		else if ((strncmp ("allow_codec_", key, strlen ("allow_codec_")) == 0)
				|| (strncmp ("bwinlast", key, strlen ("bwinlast")) == 0)
				|| (strncmp ("bwoutlast", key, strlen ("bwoutlast")) == 0)
				|| (strncmp ("webpost_", key, strlen ("webpost_")) == 0)
				|| (strcmp ("adminemail", key) == 0)
				|| (strcmp ("clan_server", key) == 0)
				|| (strcmp ("countrynumber", key) == 0)
				|| (strcmp ("id", key) == 0)
				|| (strcmp ("ispname", key) == 0)
				|| (strcmp ("linkurl", key) == 0)
				|| (strcmp ("maxusers", key) == 0)
				|| (strcmp ("name", key) == 0)
				|| (strcmp ("password", key) == 0)
				|| (strcmp ("platform", key) == 0)
				|| (strcmp ("server_platform", key) == 0)
				|| (strcmp ("server_uptime", key) == 0)
				|| (strcmp ("server_version", key) == 0)
				|| (strcmp ("udpport", key) == 0)
				|| (strcmp ("uptime", key) == 0)
				|| (strcmp ("users_maximal", key) == 0)
				|| (strcmp ("welcomemessage", key) == 0))
			/* ignore */;
		else
		{
			INFO ("teamspeak2 plugin: Unknown key-value-pair: "
					"key = %s; value = %s;", key, value);
		}
	} /* while (42) */

	/* Collect vserver packet loss rates only if the loop above did not exit
	 * with an error. */
	if ((status == 0) && (vserver != NULL))
	{
		status = tss2_vserver_gapl (read_fh, write_fh, vserver, &packet_loss);
		if (status == 0)
		{
			valid |= 0x20;
		}
		else
		{
			WARNING ("teamspeak2 plugin: Reading package loss "
					"for vserver %i failed.", vserver->port);
		}
	}

	if ((valid & 0x01) == 0x01)
		tss2_submit_gauge (plugin_instance, "users", NULL, users);

	if ((valid & 0x06) == 0x06)
		tss2_submit_io (plugin_instance, "io_octets", rx_octets, tx_octets);

	if ((valid & 0x18) == 0x18)
		tss2_submit_io (plugin_instance, "io_packets", rx_packets, tx_packets);

	if ((valid & 0x20) == 0x20)
		tss2_submit_gauge (plugin_instance, "percent", "packet_loss", packet_loss);

	if ((valid & 0x40) == 0x40)
		tss2_submit_gauge (plugin_instance, "gauge", "channels", channels);

	if ((valid & 0x80) == 0x80)
		tss2_submit_gauge (plugin_instance, "gauge", "servers", servers);

	if (valid == 0)
		return (-1);
	return (0);
}