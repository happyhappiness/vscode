static BOOL disable_deltas_p(void)
{
	extern int whole_file, no_whole_file;
	extern int local_server;
	extern int write_batch;

	assert(whole_file == 0 || whole_file == 1);

	/* whole_file and no_whole_file are never both on at the same time */

	if (whole_file)
		return True;
	else if (no_whole_file)
		return False;
	else if (write_batch)
		return False;
	else
		return local_server;
}