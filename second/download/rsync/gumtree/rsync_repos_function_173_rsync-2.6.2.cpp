static BOOL disable_deltas_p(void)
{
	if (whole_file > 0)
		return True;
	if (whole_file == 0 || write_batch)
		return False;
	return local_server;
}