void diff_setup(struct diff_options *options)
{
	memcpy(options, &default_diff_options, sizeof(*options));

	options->file = stdout;

	options->line_termination = '\n';
	options->break_opt = -1;
	options->rename_limit = -1;
	options->dirstat_permille = diff_dirstat_permille_default;
	options->context = diff_context_default;
	DIFF_OPT_SET(options, RENAME_EMPTY);

	/* pathchange left =NULL by default */
	options->change = diff_change;
	options->add_remove = diff_addremove;
	options->use_color = diff_use_color_default;
	options->detect_rename = diff_detect_rename_default;
	options->xdl_opts |= diff_algorithm;

	options->orderfile = diff_order_file_cfg;

	if (diff_no_prefix) {
		options->a_prefix = options->b_prefix = "";
	} else if (!diff_mnemonic_prefix) {
		options->a_prefix = "a/";
		options->b_prefix = "b/";
	}
}