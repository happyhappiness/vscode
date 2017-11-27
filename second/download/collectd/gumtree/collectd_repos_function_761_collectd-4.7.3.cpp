static void tss2_close_socket (void)
{
	/*
	 * Closes all sockets
	 */
	if (global_write_fh != NULL)
	{
		fputs ("quit\r\n", global_write_fh);
	}

	if (global_read_fh != NULL)
	{
		fclose (global_read_fh);
		global_read_fh = NULL;
	}

	if (global_write_fh != NULL)
	{
		fclose (global_write_fh);
		global_write_fh = NULL;
	}
}