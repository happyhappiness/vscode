static char *create_temp_file(unsigned char *sha1)
{
	static char path[50];
	void *buf;
	enum object_type type;
	unsigned long size;
	int fd;

	buf = read_sha1_file(sha1, &type, &size);
	if (!buf || type != OBJ_BLOB)
		die("unable to read blob object %s", sha1_to_hex(sha1));

	xsnprintf(path, sizeof(path), ".merge_file_XXXXXX");
	fd = xmkstemp(path);
	if (write_in_full(fd, buf, size) != size)
		die_errno("unable to write temp-file");
	close(fd);
	return path;
}