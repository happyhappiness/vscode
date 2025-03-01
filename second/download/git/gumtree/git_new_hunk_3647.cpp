{
	if (rev->shown_one) {
		rev->shown_one = 0;
		if (rev->commit_format != CMIT_FMT_ONELINE)
			putchar(rev->diffopt.line_termination);
	}
	fprintf(rev->diffopt.file, _("Final output: %d %s\n"), nr, stage);
}

static struct itimerval early_output_timer;

static void log_show_early(struct rev_info *revs, struct commit_list *list)
{
	int i = revs->early_output, close_file = revs->diffopt.close_file;
	int show_header = 1;

	revs->diffopt.close_file = 0;
	sort_in_topological_order(&list, revs->sort_order);
	while (list && i) {
		struct commit *commit = list->item;
		switch (simplify_commit(revs, commit)) {
		case commit_show:
			if (show_header) {
