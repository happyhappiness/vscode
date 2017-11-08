static char *unique_path(struct merge_options *o, const char *path, const char *branch)
{
	struct strbuf newpath = STRBUF_INIT;
	int suffix = 0;
	struct stat st;
	size_t base_len;

	strbuf_addf(&newpath, "%s~", path);
	add_flattened_path(&newpath, branch);

	base_len = newpath.len;
	while (string_list_has_string(&o->current_file_set, newpath.buf) ||
	       string_list_has_string(&o->current_directory_set, newpath.buf) ||
	       lstat(newpath.buf, &st) == 0) {
		strbuf_setlen(&newpath, base_len);
		strbuf_addf(&newpath, "_%d", suffix++);
	}

	string_list_insert(&o->current_file_set, newpath.buf);
	return strbuf_detach(&newpath, NULL);
}