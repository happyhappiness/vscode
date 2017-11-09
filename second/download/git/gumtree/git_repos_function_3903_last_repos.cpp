static void graph_show_line_prefix(const struct diff_options *diffopt)
{
	if (!diffopt || !diffopt->line_prefix)
		return;

	fwrite(diffopt->line_prefix,
	       sizeof(char),
	       diffopt->line_prefix_length,
	       diffopt->file);
}