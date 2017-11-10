static void diff_tree_tweak_rev(struct rev_info *rev, struct setup_revision_opt *opt)
{
	if (!rev->diffopt.output_format) {
		if (rev->dense_combined_merges)
			rev->diffopt.output_format = DIFF_FORMAT_PATCH;
		else
			rev->diffopt.output_format = DIFF_FORMAT_RAW;
	}
}