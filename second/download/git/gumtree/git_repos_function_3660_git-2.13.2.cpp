static int save_files_dirs(const unsigned char *sha1,
		struct strbuf *base, const char *path,
		unsigned int mode, int stage, void *context)
{
	int baselen = base->len;
	struct merge_options *o = context;

	strbuf_addstr(base, path);

	if (S_ISDIR(mode))
		string_list_insert(&o->current_directory_set, base->buf);
	else
		string_list_insert(&o->current_file_set, base->buf);

	strbuf_setlen(base, baselen);
	return (S_ISDIR(mode) ? READ_TREE_RECURSIVE : 0);
}