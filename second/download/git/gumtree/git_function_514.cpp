static int daemon_error(const char *dir, const char *msg)
{
	if (!informative_errors)
		msg = "access denied or repository not exported";
	packet_write(1, "ERR %s: %s", msg, dir);
	return -1;
}