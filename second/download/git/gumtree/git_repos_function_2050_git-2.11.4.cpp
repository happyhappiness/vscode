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