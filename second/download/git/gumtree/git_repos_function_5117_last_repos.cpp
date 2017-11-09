static int blame_move_callback(const struct option *option, const char *arg, int unset)
{
	int *opt = option->value;

	*opt |= PICKAXE_BLAME_MOVE;

	if (arg)
		blame_move_score = parse_score(arg);
	return 0;
}