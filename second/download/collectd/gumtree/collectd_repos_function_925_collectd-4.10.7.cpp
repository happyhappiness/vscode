static int tss2_vserver_gapl (FILE *read_fh, FILE *write_fh,
		gauge_t *ret_value)
{
	/*
	 * Reads the vserver's average packet loss and submits it to collectd.
	 * Be sure to run the tss2_read_vserver function before calling this so
	 * the vserver is selected correctly.
	 */
	gauge_t packet_loss = NAN;
	int status;

	status = tss2_send_request (write_fh, "gapl\r\n");
	if (status != 0)
	{
		ERROR("teamspeak2 plugin: tss2_send_request (gapl) failed.");
		return (-1);
	}

	while (42)
	{
		char buffer[4096];
		char *value;
		char *endptr = NULL;
		
		status = tss2_receive_line (read_fh, buffer, sizeof (buffer));
		if (status != 0)
		{
			/* Set to NULL just to make sure noone uses these FHs anymore. */
			read_fh = NULL;
			write_fh = NULL;
			ERROR ("teamspeak2 plugin: tss2_receive_line failed.");
			return (-1);
		}
		buffer[sizeof (buffer) - 1] = 0;
		
		if (strncmp ("average_packet_loss=", buffer,
					strlen ("average_packet_loss=")) == 0)
		{
			/* Got average packet loss, now interpret it */
			value = &buffer[20];
			/* Replace , with . */
			while (*value != 0)
			{
				if (*value == ',')
				{
					*value = '.';
					break;
				}
				value++;
			}
			
			value = &buffer[20];
			
			packet_loss = strtod (value, &endptr);
			if (value == endptr)
			{
				/* Failed */
				WARNING ("teamspeak2 plugin: Could not read average package "
						"loss from string: %s", buffer);
				continue;
			}
		}
		else if (strncasecmp ("OK", buffer, 2) == 0)
		{
			break;
		}
		else if (strncasecmp ("ERROR", buffer, 5) == 0)
		{
			ERROR ("teamspeak2 plugin: Server returned an error: %s", buffer);
			return (-1);
		}
		else
		{
			WARNING ("teamspeak2 plugin: Server returned unexpected string: %s",
					buffer);
		}
	}
	
	*ret_value = packet_loss;
	return (0);
}