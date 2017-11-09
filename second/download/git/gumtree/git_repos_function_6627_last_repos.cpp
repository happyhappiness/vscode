static inline int mingw_is_dir_sep(int c)
{
	return c == '/' || c == '\\';
}