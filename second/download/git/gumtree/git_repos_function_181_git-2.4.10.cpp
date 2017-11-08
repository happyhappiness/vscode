void show_combined_diff(struct combine_diff_path *p,
		       int num_parent,
		       int dense,
		       struct rev_info *rev)
{
	struct diff_options *opt = &rev->diffopt;

	if (opt->output_format & (DIFF_FORMAT_RAW |
				  DIFF_FORMAT_NAME |
				  DIFF_FORMAT_NAME_STATUS))
		show_raw_diff(p, num_parent, rev);
	else if (opt->output_format & DIFF_FORMAT_PATCH)
		show_patch_diff(p, num_parent, dense, 1, rev);
}