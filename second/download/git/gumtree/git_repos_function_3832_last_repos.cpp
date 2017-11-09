void init_merge_options(struct merge_options *o)
{
	memset(o, 0, sizeof(struct merge_options));
	o->verbosity = 2;
	o->buffer_output = 1;
	o->diff_rename_limit = -1;
	o->merge_rename_limit = -1;
	o->renormalize = 0;
	o->detect_rename = 1;
	merge_recursive_config(o);
	if (getenv("GIT_MERGE_VERBOSITY"))
		o->verbosity =
			strtol(getenv("GIT_MERGE_VERBOSITY"), NULL, 10);
	if (o->verbosity >= 5)
		o->buffer_output = 0;
	strbuf_init(&o->obuf, 0);
	string_list_init(&o->current_file_set, 1);
	string_list_init(&o->current_directory_set, 1);
	string_list_init(&o->df_conflict_file_set, 1);
}