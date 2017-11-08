int git_open(const char *name)
{
	static int sha1_file_open_flag = O_NOATIME | O_CLOEXEC;

	for (;;) {
		int fd;

		errno = 0;
		fd = open(name, O_RDONLY | sha1_file_open_flag);
		if (fd >= 0)
			return fd;

		/* Try again w/o O_CLOEXEC: the kernel might not support it */
		if ((sha1_file_open_flag & O_CLOEXEC) && errno == EINVAL) {
			sha1_file_open_flag &= ~O_CLOEXEC;
			continue;
		}

		/* Might the failure be due to O_NOATIME? */
		if (errno != ENOENT && (sha1_file_open_flag & O_NOATIME)) {
			sha1_file_open_flag &= ~O_NOATIME;
			continue;
		}
		return -1;
	}
}