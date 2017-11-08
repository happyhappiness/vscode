static void copy_obj_to_fd(int fd, const unsigned char *sha1)
{
	unsigned long size;
	enum object_type type;
	char *buf = read_sha1_file(sha1, &type, &size);
	if (buf) {
		if (size)
			write_or_die(fd, buf, size);
		free(buf);
	}
}