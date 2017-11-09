const char *blame_nth_line(struct blame_scoreboard *sb, long lno)
{
	return sb->final_buf + sb->lineno[lno];
}