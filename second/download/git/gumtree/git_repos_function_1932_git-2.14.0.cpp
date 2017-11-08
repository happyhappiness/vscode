static inline int is_missing_file_error(int errno_)
{
	return (errno_ == ENOENT || errno_ == ENOTDIR);
}