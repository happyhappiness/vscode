static void diff_summary(struct diff_options *opt, struct diff_filepair *p)
{
	FILE *file = opt->file;
	const char *line_prefix = diff_line_prefix(opt);

	switch(p->status) {
	case DIFF_STATUS_DELETED:
		fputs(line_prefix, file);
		show_file_mode_name(file, "delete", p->one);
		break;
	case DIFF_STATUS_ADDED:
		fputs(line_prefix, file);
		show_file_mode_name(file, "create", p->two);
		break;
	case DIFF_STATUS_COPIED:
		fputs(line_prefix, file);
		show_rename_copy(file, "copy", p, line_prefix);
		break;
	case DIFF_STATUS_RENAMED:
		fputs(line_prefix, file);
		show_rename_copy(file, "rename", p, line_prefix);
		break;
	default:
		if (p->score) {
			fprintf(file, "%s rewrite ", line_prefix);
			write_name_quoted(p->two->path, file, ' ');
			fprintf(file, "(%d%%)\n", similarity_index(p));
		}
		show_mode_change(file, p, !p->score, line_prefix);
		break;
	}
}