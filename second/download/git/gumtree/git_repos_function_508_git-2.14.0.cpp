void init_scoreboard(struct blame_scoreboard *sb)
{
	memset(sb, 0, sizeof(struct blame_scoreboard));
	sb->move_score = BLAME_DEFAULT_MOVE_SCORE;
	sb->copy_score = BLAME_DEFAULT_COPY_SCORE;
}