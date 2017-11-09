char *find_pathspecs_matching_against_index(const struct pathspec *pathspec,
					    const struct index_state *istate)
{
	char *seen = xcalloc(pathspec->nr, 1);
	add_pathspec_matches_against_index(pathspec, istate, seen);
	return seen;
}