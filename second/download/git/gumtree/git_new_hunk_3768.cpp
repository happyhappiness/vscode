	return showed_log;
}

int log_tree_commit(struct rev_info *opt, struct commit *commit)
{
	struct log_info log;
	int shown, close_file = opt->diffopt.close_file;

	log.commit = commit;
	log.parent = NULL;
	opt->loginfo = &log;
	opt->diffopt.close_file = 0;

	if (opt->line_level_traverse)
		return line_log_print(opt, commit);

	if (opt->track_linear && !opt->linear && !opt->reverse_output_stage)
		fprintf(opt->diffopt.file, "\n%s\n", opt->break_bar);
	shown = log_tree_diff(opt, commit, &log);
	if (!shown && opt->loginfo && opt->always_show_header) {
		log.parent = NULL;
		show_log(opt);
		shown = 1;
	}
	if (opt->track_linear && !opt->linear && opt->reverse_output_stage)
		fprintf(opt->diffopt.file, "\n%s\n", opt->break_bar);
	opt->loginfo = NULL;
	maybe_flush_or_die(opt->diffopt.file, "stdout");
	if (close_file)
		fclose(opt->diffopt.file);
	return shown;
}
