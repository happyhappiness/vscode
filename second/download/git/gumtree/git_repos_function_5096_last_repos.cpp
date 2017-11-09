static const char *nth_line_cb(void *data, long lno)
{
	return blame_nth_line((struct blame_scoreboard *)data, lno);
}