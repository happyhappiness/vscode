	struct strbuf filename = STRBUF_INIT;
	int suffix_len = strlen(rev->patch_suffix) + 1;

	if (output_directory) {
		strbuf_addstr(&filename, output_directory);
		if (filename.len >=
		    PATH_MAX - FORMAT_PATCH_NAME_MAX - suffix_len)
			return error(_("name of output directory is too long"));
		strbuf_complete(&filename, '/');
	}

	if (rev->numbered_files)
		strbuf_addf(&filename, "%d", rev->nr);
	else if (commit)
