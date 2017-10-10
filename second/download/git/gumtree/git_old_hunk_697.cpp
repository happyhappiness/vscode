			strbuf_addstr(&err_msg, hints_msg);
		*errs = error("%s", err_msg.buf);
		strbuf_release(&err_msg);
	}
}

static void error_removing_concrete_submodules(struct string_list *files, int *errs)
{
	print_error_files(files,
			  Q_("the following submodule (or one of its nested "
			     "submodules)\n"
			     "uses a .git directory:",
			     "the following submodules (or one of their nested "
			     "submodules)\n"
			     "use a .git directory:", files->nr),
			  _("\n(use 'rm -rf' if you really want to remove "
			    "it including all of its history)"),
			  errs);
	string_list_clear(files, 0);
}

static int check_submodules_use_gitfiles(void)
{
	int i;
	int errs = 0;
	struct string_list files = STRING_LIST_INIT_NODUP;

	for (i = 0; i < list.nr; i++) {
		const char *name = list.entry[i].name;
		int pos;
		const struct cache_entry *ce;

		pos = cache_name_pos(name, strlen(name));
