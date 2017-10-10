	int require_work_tree = 0, show_tag = 0, i;
	const char *max_prefix;
	struct dir_struct dir;
	struct exclude_list *el;
	struct string_list exclude_list = STRING_LIST_INIT_NODUP;
	struct option builtin_ls_files_options[] = {
		{ OPTION_CALLBACK, 'z', NULL, NULL, NULL,
			N_("paths are separated with NUL character"),
			PARSE_OPT_NOARG, option_parse_z },
		OPT_BOOL('t', NULL, &show_tag,
			N_("identify the file status with tags")),
		OPT_BOOL('v', NULL, &show_valid_bit,
			N_("use lowercase letters for 'assume unchanged' files")),
		OPT_BOOL('c', "cached", &show_cached,
			N_("show cached files in the output (default)")),
