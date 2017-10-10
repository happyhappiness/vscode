	    write_locked_index(&the_index, lock, COMMIT_LOCK))
		return error(_("Unable to write index."));

	return clean ? 0 : 1;
}

static int merge_recursive_config(const char *var, const char *value, void *cb)
{
	struct merge_options *o = cb;
	if (!strcmp(var, "merge.verbosity")) {
		o->verbosity = git_config_int(var, value);
		return 0;
	}
	if (!strcmp(var, "diff.renamelimit")) {
		o->diff_rename_limit = git_config_int(var, value);
		return 0;
	}
	if (!strcmp(var, "merge.renamelimit")) {
		o->merge_rename_limit = git_config_int(var, value);
		return 0;
	}
	return git_xmerge_config(var, value, cb);
}

void init_merge_options(struct merge_options *o)
{
	memset(o, 0, sizeof(struct merge_options));
	o->verbosity = 2;
	o->buffer_output = 1;
	o->diff_rename_limit = -1;
	o->merge_rename_limit = -1;
	o->renormalize = 0;
	git_config(merge_recursive_config, o);
	if (getenv("GIT_MERGE_VERBOSITY"))
		o->verbosity =
			strtol(getenv("GIT_MERGE_VERBOSITY"), NULL, 10);
	if (o->verbosity >= 5)
		o->buffer_output = 0;
	strbuf_init(&o->obuf, 0);
