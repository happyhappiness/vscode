char *find_pathspecs_matching_against_index(const struct pathspec *pathspec)
{
	char *seen = xcalloc(pathspec->nr, 1);
	add_pathspec_matches_against_index(pathspec, seen);
	return seen;
}