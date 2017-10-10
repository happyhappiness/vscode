	    write_locked_index(&the_index, lock, COMMIT_LOCK))
		return error(_("Unable to write index."));

	return clean ? 0 : 1;
}

static void merge_recursive_config(struct merge_options *o)
{
	git_config_get_int("merge.verbosity", &o->verbosity);
	git_config_get_int("diff.renamelimit", &o->diff_rename_limit);
	git_config_get_int("merge.renamelimit", &o->merge_rename_limit);
	git_config(git_xmerge_config, NULL);
}

void init_merge_options(struct merge_options *o)
{
	memset(o, 0, sizeof(struct merge_options));
	o->verbosity = 2;
	o->buffer_output = 1;
	o->diff_rename_limit = -1;
	o->merge_rename_limit = -1;
	o->renormalize = 0;
	merge_recursive_config(o);
	if (getenv("GIT_MERGE_VERBOSITY"))
		o->verbosity =
			strtol(getenv("GIT_MERGE_VERBOSITY"), NULL, 10);
	if (o->verbosity >= 5)
		o->buffer_output = 0;
	strbuf_init(&o->obuf, 0);
