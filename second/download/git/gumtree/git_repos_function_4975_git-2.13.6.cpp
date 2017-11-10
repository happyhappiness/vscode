static const char *nth_line(struct scoreboard *sb, long lno)
{
	return sb->final_buf + sb->lineno[lno];
}