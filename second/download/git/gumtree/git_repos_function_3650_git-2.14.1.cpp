static inline int would_convert_to_git(const struct index_state *istate,
				       const char *path)
{
	return convert_to_git(istate, path, NULL, 0, NULL, 0);
}