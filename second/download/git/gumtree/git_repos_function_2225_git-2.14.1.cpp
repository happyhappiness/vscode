static int open_sha1_file(const unsigned char *sha1, const char **path)
{
	int fd;
	struct alternate_object_database *alt;
	int most_interesting_errno;

	*path = sha1_file_name(sha1);
	fd = git_open(*path);
	if (fd >= 0)
		return fd;
	most_interesting_errno = errno;

	prepare_alt_odb();
	for (alt = alt_odb_list; alt; alt = alt->next) {
		*path = alt_sha1_path(alt, sha1);
		fd = git_open(*path);
		if (fd >= 0)
			return fd;
		if (most_interesting_errno == ENOENT)
			most_interesting_errno = errno;
	}
	errno = most_interesting_errno;
	return -1;
}