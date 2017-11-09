static inline int git_offset_1st_component(const char *path)
{
	return is_dir_sep(path[0]);
}