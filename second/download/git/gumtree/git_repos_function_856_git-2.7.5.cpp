static inline ssize_t write_str_in_full(int fd, const char *str)
{
	return write_in_full(fd, str, strlen(str));
}