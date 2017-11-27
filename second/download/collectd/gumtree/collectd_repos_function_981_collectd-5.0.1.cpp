static int tss2_receive_line (FILE *fh, char *buffer, int buffer_size)
{
	/*
	 * Receive a single line from the given file object
	 */
	char *temp;
	 
	/*
	 * fgets is blocking but much easier then doing anything else
	 * TODO: Non-blocking Version would be safer
	 */
	temp = fgets (buffer, buffer_size, fh);
	if (temp == NULL)
	{
		char errbuf[1024];
		ERROR ("teamspeak2 plugin: fgets failed: %s",
				sstrerror (errno, errbuf, sizeof(errbuf)));
		tss2_close_socket ();
		return (-1);
	}

	buffer[buffer_size - 1] = 0;
	return (0);
}