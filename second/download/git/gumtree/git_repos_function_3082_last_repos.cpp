static int ends_with_blank_line(const char *buf, size_t len)
{
	int ll = last_line(buf, len);
	if (ll < 0)
		return 0;
	return is_blank_line(buf + ll);
}