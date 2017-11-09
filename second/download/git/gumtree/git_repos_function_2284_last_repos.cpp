static void close_sha1_file(int fd)
{
	if (fsync_object_files)
		fsync_or_die(fd, "sha1 file");
	if (close(fd) != 0)
		die_errno("error when closing sha1 file");
}