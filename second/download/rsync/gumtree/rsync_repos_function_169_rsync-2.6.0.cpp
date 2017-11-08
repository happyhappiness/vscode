static BOOL disable_deltas_p(void)
{
	extern int whole_file;
	extern int local_server;
	extern int write_batch;

	if (whole_file > 0)
		return True;
	if (whole_file == 0 || write_batch)
		return False;
	return local_server;
}