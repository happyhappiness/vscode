static char *prepare_final(struct scoreboard *sb)
{
	const char *name;
	sb->final = find_single_final(sb->revs, &name);
	return xstrdup_or_null(name);
}