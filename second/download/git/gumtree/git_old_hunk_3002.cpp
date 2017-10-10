	return do_plain_rerere(&merge_rr, fd);
}

static int rerere_forget_one_path(const char *path, struct string_list *rr)
{
	const char *filename;
	char *hex;
	unsigned char sha1[20];
	int ret;

	ret = handle_cache(path, sha1, NULL);
	if (ret < 1)
		return error("Could not parse conflict hunks in '%s'", path);
	hex = xstrdup(sha1_to_hex(sha1));
	filename = rerere_path(hex, "postimage");
	if (unlink(filename))
		return (errno == ENOENT
			? error("no remembered resolution for %s", path)
			: error("cannot unlink %s: %s", filename, strerror(errno)));

	handle_cache(path, sha1, rerere_path(hex, "preimage"));
	fprintf(stderr, "Updated preimage for '%s'\n", path);


	string_list_insert(rr, path)->util = hex;
	fprintf(stderr, "Forgot resolution for %s\n", path);
	return 0;
}

int rerere_forget(struct pathspec *pathspec)
{
