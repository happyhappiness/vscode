static void end_headers(void)
{
	write_or_die(1, "\r\n", 2);
}