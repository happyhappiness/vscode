	}
	git_SHA1_Final(real_sha1, &c);
	close_istream(st);
	return hashcmp(sha1, real_sha1) ? -1 : 0;
}

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

static int stat_sha1_file(const unsigned char *sha1, struct stat *st)
{
	struct alternate_object_database *alt;

	if (!lstat(sha1_file_name(sha1), st))
		return 0;

	prepare_alt_odb();
	errno = ENOENT;
	for (alt = alt_odb_list; alt; alt = alt->next) {
		const char *path = alt_sha1_path(alt, sha1);
		if (!lstat(path, st))
			return 0;
	}

	return -1;
}

static int open_sha1_file(const unsigned char *sha1)
{
	int fd;
	struct alternate_object_database *alt;
	int most_interesting_errno;

	fd = git_open(sha1_file_name(sha1));
	if (fd >= 0)
		return fd;
	most_interesting_errno = errno;

	prepare_alt_odb();
	for (alt = alt_odb_list; alt; alt = alt->next) {
		const char *path = alt_sha1_path(alt, sha1);
		fd = git_open(path);
		if (fd >= 0)
			return fd;
		if (most_interesting_errno == ENOENT)
			most_interesting_errno = errno;
	}
	errno = most_interesting_errno;
	return -1;
}

void *map_sha1_file(const unsigned char *sha1, unsigned long *size)
{
	void *map;
	int fd;

	fd = open_sha1_file(sha1);
	map = NULL;
	if (fd >= 0) {
		struct stat st;

		if (!fstat(fd, &st)) {
			*size = xsize_t(st.st_size);
			if (!*size) {
				/* mmap() is forbidden on empty files */
				error("object file %s is empty", sha1_file_name(sha1));
				return NULL;
			}
			map = xmmap(NULL, *size, PROT_READ, MAP_PRIVATE, fd, 0);
		}
		close(fd);
	}
	return map;
}

unsigned long unpack_object_header_buffer(const unsigned char *buf,
		unsigned long len, enum object_type *type, unsigned long *sizep)
{
	unsigned shift;
	unsigned long size, c;
	unsigned long used = 0;
