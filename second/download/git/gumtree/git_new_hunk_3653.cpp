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

