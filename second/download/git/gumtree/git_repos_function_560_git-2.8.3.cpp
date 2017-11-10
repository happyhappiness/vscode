int git_config_with_options(config_fn_t fn, void *data,
			    struct git_config_source *config_source,
			    int respect_includes)
{
	struct config_include_data inc = CONFIG_INCLUDE_INIT;

	if (respect_includes) {
		inc.fn = fn;
		inc.data = data;
		fn = git_config_include;
		data = &inc;
	}

	/*
	 * If we have a specific filename, use it. Otherwise, follow the
	 * regular lookup sequence.
	 */
	if (config_source && config_source->use_stdin)
		return git_config_from_stdin(fn, data);
	else if (config_source && config_source->file)
		return git_config_from_file(fn, config_source->file, data);
	else if (config_source && config_source->blob)
		return git_config_from_blob_ref(fn, config_source->blob, data);

	return do_git_config_sequence(fn, data);
}