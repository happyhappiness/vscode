void *read_sha1_file_extended(const unsigned char *sha1,
			      enum object_type *type,
			      unsigned long *size,
			      unsigned flag)
{
	void *data;
	const struct packed_git *p;
	const unsigned char *repl = lookup_replace_object_extended(sha1, flag);

	errno = 0;
	data = read_object(repl, type, size);
	if (data)
		return data;

	if (errno && errno != ENOENT)
		die_errno("failed to read object %s", sha1_to_hex(sha1));

	/* die if we replaced an object with one that does not exist */
	if (repl != sha1)
		die("replacement %s not found for %s",
		    sha1_to_hex(repl), sha1_to_hex(sha1));

	if (has_loose_object(repl)) {
		const char *path = sha1_file_name(sha1);

		die("loose object %s (stored in %s) is corrupt",
		    sha1_to_hex(repl), path);
	}

	if ((p = has_packed_and_bad(repl)) != NULL)
		die("packed object %s (stored in %s) is corrupt",
		    sha1_to_hex(repl), p->pack_name);

	return NULL;
}