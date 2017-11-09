void write_file_buf(const char *path, const char *buf, size_t len)
{
	int fd = xopen(path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (write_in_full(fd, buf, len) != len)
		die_errno(_("could not write to %s"), path);
	if (close(fd))
		die_errno(_("could not close %s"), path);
}