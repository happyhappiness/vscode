		die("%s is not a valid object", sha1_to_hex(sha1));
	if (type != expect)
		die("%s is not a valid '%s' object", sha1_to_hex(sha1),
		    typename(expect));
}

static int for_each_file_in_obj_subdir(int subdir_nr,
				       struct strbuf *path,
				       each_loose_object_fn obj_cb,
				       each_loose_cruft_fn cruft_cb,
				       each_loose_subdir_fn subdir_cb,
				       void *data)
{
	size_t baselen = path->len;
	DIR *dir = opendir(path->buf);
	struct dirent *de;
	int r = 0;

	if (!dir) {
		if (errno == ENOENT)
			return 0;
		return error_errno("unable to open %s", path->buf);
	}

	while ((de = readdir(dir))) {
		if (is_dot_or_dotdot(de->d_name))
			continue;

