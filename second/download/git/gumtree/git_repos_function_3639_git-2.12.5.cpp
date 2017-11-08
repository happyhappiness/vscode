void graph_setup_line_prefix(struct diff_options *diffopt)
{
	default_diffopt = diffopt;

	/* setup an output prefix callback if necessary */
	if (diffopt && !diffopt->output_prefix)
		diffopt->output_prefix = diff_output_prefix_callback;
}