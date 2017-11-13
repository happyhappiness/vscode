static int open_next_file(struct commit *commit, const char *subject,
			 struct rev_info *rev, int quiet)
{
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
		fmt_output_commit(&filename, commit, rev);
	else
		fmt_output_subject(&filename, subject, rev);

	if (!quiet)
		printf("%s\n", filename.buf + outdir_offset);

	if ((rev->diffopt.file = fopen(filename.buf, "w")) == NULL)
		return error(_("Cannot open patch file %s"), filename.buf);

	strbuf_release(&filename);
	return 0;
}