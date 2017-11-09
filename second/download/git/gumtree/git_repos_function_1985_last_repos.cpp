static int read_mailmap_blob(struct string_list *map,
			     const char *name,
			     char **repo_abbrev)
{
	unsigned char sha1[20];
	char *buf;
	unsigned long size;
	enum object_type type;

	if (!name)
		return 0;
	if (get_sha1(name, sha1) < 0)
		return 0;

	buf = read_sha1_file(sha1, &type, &size);
	if (!buf)
		return error("unable to read mailmap object at %s", name);
	if (type != OBJ_BLOB)
		return error("mailmap is not a blob: %s", name);

	read_mailmap_string(map, buf, repo_abbrev);

	free(buf);
	return 0;
}