static inline int matches_tree_write_stack(struct tree_write_stack *tws,
		const char *full_path)
{
	return  full_path[0] == tws->path[0] &&
		full_path[1] == tws->path[1] &&
		full_path[2] == '/';
}