static void show_mode_change(FILE *file, struct diff_filepair *p, int show_name,
		const char *line_prefix)
{
	if (p->one->mode && p->two->mode && p->one->mode != p->two->mode) {
		fprintf(file, "%s mode change %06o => %06o%c", line_prefix, p->one->mode,
			p->two->mode, show_name ? ' ' : '\n');
		if (show_name) {
			write_name_quoted(p->two->path, file, '\n');
		}
	}
}