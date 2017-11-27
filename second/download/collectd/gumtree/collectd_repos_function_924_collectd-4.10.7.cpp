static int tss2_select_vserver (FILE *read_fh, FILE *write_fh, vserver_list_t *vserver)
{
	/*
	 * Tell the server to select the given vserver
	 */
	char command[128];
	char response[128];
	int status;

	/* Send request */
	ssnprintf (command, sizeof (command), "sel %i\r\n", vserver->port);

	status = tss2_send_request (write_fh, command);
	if (status != 0)
	{
		ERROR ("teamspeak2 plugin: tss2_send_request (%s) failed.", command);
		return (-1);
	}

	/* Get answer */
	status = tss2_receive_line (read_fh, response, sizeof (response));
	if (status != 0)
	{
		ERROR ("teamspeak2 plugin: tss2_receive_line failed.");
		return (-1);
	}
	response[sizeof (response) - 1] = 0;

	/* Check answer */
	if ((strncasecmp ("OK", response, 2) == 0)
			&& ((response[2] == 0)
				|| (response[2] == '\n')
				|| (response[2] == '\r')))
		return (0);

	ERROR ("teamspeak2 plugin: Command ``%s'' failed. "
			"Response received from server was: ``%s''.",
			command, response);
	return (-1);
}