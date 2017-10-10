	 * appear in the output before it is renamed (e.g., when a file
	 * was copied and renamed in the same commit).
	 */
	return (a->status == 'R') - (b->status == 'R');
}

static void print_path(const char *path)
{
	int need_quote = quote_c_style(path, NULL, NULL, 0);
	if (need_quote)
		quote_c_style(path, NULL, stdout, 0);
	else if (strchr(path, ' '))
		printf("\"%s\"", path);
	else
		printf("%s", path);
}

static void show_filemodify(struct diff_queue_struct *q,
			    struct diff_options *options, void *data)
{
	int i;

	/*
