static int create_tmpfile(char *buffer, size_t bufsiz, const char *filename)
{
	int fd, dirlen = directory_size(filename);

	if (dirlen + 20 > bufsiz) {
		errno = ENAMETOOLONG;
		return -1;
	}
	memcpy(buffer, filename, dirlen);
	strcpy(buffer + dirlen, "tmp_obj_XXXXXX");
	fd = git_mkstemp_mode(buffer, 0444);
	if (fd < 0 && dirlen && errno == ENOENT) {
		/* Make sure the directory exists */
		memcpy(buffer, filename, dirlen);
		buffer[dirlen-1] = 0;
		if (mkdir(buffer, 0777) && errno != EEXIST)
			return -1;
		if (adjust_shared_perm(buffer))
			return -1;

		/* Try again */
		strcpy(buffer + dirlen - 1, "/tmp_obj_XXXXXX");
		fd = git_mkstemp_mode(buffer, 0444);
	}
	return fd;
}