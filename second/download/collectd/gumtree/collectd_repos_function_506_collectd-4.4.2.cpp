static int tss2_send_request (FILE *fh, const char *request)
{
	/*
	 * This function puts a request to the server socket
	 */
	int status;

	status = fputs (request, fh);
	if (status < 0)
	{
		ERROR ("teamspeak2 plugin: fputs failed.");
		tss2_close_socket ();
		return (-1);
	}
	fflush (fh);

	return (0);
}