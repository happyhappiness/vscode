static const char *nth_line_cb(void *data, long lno)
{
	return nth_line((struct scoreboard *)data, lno);
}