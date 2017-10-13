static void builtin_diffstat(const char *name_a, const char *name_b,
			     struct diff_filespec *one,
			     struct diff_filespec *two,
			     struct diffstat_t *diffstat,
			     struct diff_options *o,
			     struct diff_filepair *p)
{
	mmfile_t mf1, mf2;
	struct diffstat_file *data;
	int same_contents;
	int complete_rewrite = 0;

	if (!DIFF_PAIR_UNMERGED(p)) {
		if (p->status == DIFF_STATUS_MODIFIED && p->score)
			complete_rewrite = 1;
	}

	data = diffstat_add(diffstat, name_a, name_b);
	data->is_interesting = p->status != DIFF_STATUS_UNKNOWN;

	if (!one || !two) {
		data->is_unmerged = 1;
		return;
	}

	same_contents = !hashcmp(one->sha1, two->sha1);

	if (diff_filespec_is_binary(one) || diff_filespec_is_binary(two)) {
		data->is_binary = 1;
		if (same_contents) {
			data->added = 0;
			data->deleted = 0;
		} else {
			data->added = diff_filespec_size(two);
			data->deleted = diff_filespec_size(one);
		}
	}

	else if (complete_rewrite) {
		diff_populate_filespec(one, 0);
		diff_populate_filespec(two, 0);
		data->deleted = count_lines(one->data, one->size);
		data->added = count_lines(two->data, two->size);
	}

	else if (!same_contents) {
		/* Crazy xdl interfaces.. */
		xpparam_t xpp;
		xdemitconf_t xecfg;

		if (fill_mmfile(&mf1, one) < 0 || fill_mmfile(&mf2, two) < 0)
			die("unable to read files to diff");

		memset(&xpp, 0, sizeof(xpp));
		memset(&xecfg, 0, sizeof(xecfg));
		xpp.flags = o->xdl_opts;
		xecfg.ctxlen = o->context;
		xecfg.interhunkctxlen = o->interhunkcontext;
		if (xdi_diff_outf(&mf1, &mf2, diffstat_consume, diffstat,
				  &xpp, &xecfg))
			die("unable to generate diffstat for %s", one->path);
	}

	diff_free_filespec_data(one);
	diff_free_filespec_data(two);
}