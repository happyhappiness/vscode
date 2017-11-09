int submodule_path_match(const struct pathspec *ps,
			 const char *submodule_name,
			 char *seen)
{
	int matched = do_match_pathspec(ps, submodule_name,
					strlen(submodule_name),
					0, seen,
					DO_MATCH_DIRECTORY |
					DO_MATCH_SUBMODULE);
	return matched;
}