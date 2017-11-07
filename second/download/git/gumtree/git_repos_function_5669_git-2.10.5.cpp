static void hash_fd(int fd, const char *type, const char *path, unsigned flags,
		    int literally)
{
	struct stat st;
	unsigned char sha1[20];

	if (fstat(fd, &st) < 0 ||
	    (literally
	     ? hash_literally(sha1, fd, type, flags)
	     : index_fd(sha1, fd, &st, type_from_string(type), path, flags)))
		die((flags & HASH_WRITE_OBJECT)
		    ? "Unable to add %s to database"
		    : "Unable to hash %s", path);
	printf("%s\n", sha1_to_hex(sha1));
	maybe_flush_or_die(stdout, "hash to stdout");
}