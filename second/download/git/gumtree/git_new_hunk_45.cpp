				   status ? DIFF_WHITESPACE : DIFF_FRAGINFO);
	reset = diff_get_color_opt(&opt->diffopt, DIFF_RESET);
	while (*bol) {
		eol = strchrnul(bol, '\n');
		printf("%s%.*s%s%s", color, (int)(eol - bol), bol, reset,
		       *eol ? "\n" : "");
		graph_show_oneline(opt->graph);
		bol = (*eol) ? (eol + 1) : eol;
	}
}

static void show_signature(struct rev_info *opt, struct commit *commit)
{
