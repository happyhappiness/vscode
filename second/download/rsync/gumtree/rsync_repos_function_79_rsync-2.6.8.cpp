void set_io_timeout(int secs)
{
	io_timeout = secs;

	if (!io_timeout || io_timeout > SELECT_TIMEOUT)
		select_timeout = SELECT_TIMEOUT;
	else
		select_timeout = io_timeout;

	allowed_lull = read_batch ? 0 : (io_timeout + 1) / 2;
}