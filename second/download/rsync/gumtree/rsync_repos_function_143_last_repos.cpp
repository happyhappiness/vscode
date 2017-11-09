void set_io_timeout(int secs)
{
	io_timeout = secs;
	allowed_lull = (io_timeout + 1) / 2;

	if (!io_timeout || allowed_lull > SELECT_TIMEOUT)
		select_timeout = SELECT_TIMEOUT;
	else
		select_timeout = allowed_lull;

	if (read_batch)
		allowed_lull = 0;
}