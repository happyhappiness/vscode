static void hash_fd(int fd, const char *type, int write_object, const char *path)
{
	struct stat st;
	unsigned char sha1[20];
	unsigned flags = (HASH_FORMAT_CHECK |
			  (write_object ? HASH_WRITE_OBJECT : 0));

	if (fstat(fd, &st) < 0 ||
	    index_fd(sha1, fd, &st, type_from_string(type), path, flags))
		die(write_object
		    ? "Unable to add %s to database"
		    : "Unable to hash %s", path);
	printf("%s\n", sha1_to_hex(sha1));
	maybe_flush_or_die(stdout, "hash to stdout");
}