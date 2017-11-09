int copy_file_with_time(const char *dst, const char *src, int mode)
{
	int status = copy_file(dst, src, mode);
	if (!status)
		return copy_times(dst, src);
	return status;
}