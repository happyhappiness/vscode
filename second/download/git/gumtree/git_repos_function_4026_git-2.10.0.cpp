const char **get_pathspec(const char *prefix, const char **pathspec)
{
	struct pathspec ps;
	parse_pathspec(&ps,
		       PATHSPEC_ALL_MAGIC &
		       ~(PATHSPEC_FROMTOP | PATHSPEC_LITERAL),
		       PATHSPEC_PREFER_CWD,
		       prefix, pathspec);
	return ps._raw;
}