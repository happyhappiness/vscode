static int is_cherry_picked_from_line(const char *buf, int len)
{
	/*
	 * We only care that it looks roughly like (cherry picked from ...)
	 */
	return len > strlen(cherry_picked_prefix) + 1 &&
		starts_with(buf, cherry_picked_prefix) && buf[len - 1] == ')';
}