static void builtin_checkdiff(const char *name_a, const char *name_b,
			      const char *attr_path,
			      struct diff_filespec *one,
			      struct diff_filespec *two,
			      struct diff_options *o)
{
	mmfile_t mf1, mf2;
	struct checkdiff_t data;

	if (!two)
		return;

	memset(&data, 0, sizeof(data));
	data.filename = name_b ? name_b : name_a;
	data.lineno = 0;
	data.o = o;
	data.ws_rule = whitespace_rule(attr_path);
	data.conflict_marker_size = ll_merge_marker_size(attr_path);

	if (fill_mmfile(&mf1, one) < 0 || fill_mmfile(&mf2, two) < 0)
		die("unable to read files to diff");

	/*
	 * All the other codepaths check both sides, but not checking
	 * the "old" side here is deliberate.  We are checking the newly
	 * introduced changes, and as long as the "new" side is text, we
	 * can and should check what it introduces.
	 */
	if (diff_filespec_is_binary(two))
		goto free_and_return;
	else {
		/* Crazy xdl interfaces.. */
		xpparam_t xpp;
		xdemitconf_t xecfg;

		memset(&xpp, 0, sizeof(xpp));
		memset(&xecfg, 0, sizeof(xecfg));
		xecfg.ctxlen = 1; /* at least one context line */
		xpp.flags = 0;
		if (xdi_diff_outf(&mf1, &mf2, checkdiff_consume, &data,
				  &xpp, &xecfg))
			die("unable to generate checkdiff for %s", one->path);

		if (data.ws_rule & WS_BLANK_AT_EOF) {
			struct emit_callback ecbdata;
			int blank_at_eof;

			ecbdata.ws_rule = data.ws_rule;
			check_blank_at_eof(&mf1, &mf2, &ecbdata);
			blank_at_eof = ecbdata.blank_at_eof_in_postimage;

			if (blank_at_eof) {
				static char *err;
				if (!err)
					err = whitespace_error_string(WS_BLANK_AT_EOF);
				fprintf(o->file, "%s:%d: %s.\n",
					data.filename, blank_at_eof, err);
				data.status = 1; /* report errors */
			}
		}
	}
 free_and_return:
	diff_free_filespec_data(one);
	diff_free_filespec_data(two);
	if (data.status)
		DIFF_OPT_SET(o, CHECK_FAILED);
}