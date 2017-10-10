	for (i = 0; i < ARRAY_SIZE(diff_temp); i++)
		if (!diff_temp[i].name)
			return diff_temp + i;
	die("BUG: diff is failing to clean up its tempfiles");
}

static int remove_tempfile_installed;

static void remove_tempfile(void)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(diff_temp); i++) {
		if (diff_temp[i].name == diff_temp[i].tmp_path)
			unlink_or_warn(diff_temp[i].name);
		diff_temp[i].name = NULL;
	}
}

static void remove_tempfile_on_signal(int signo)
{
	remove_tempfile();
	sigchain_pop(signo);
	raise(signo);
}

static void print_line_count(FILE *file, int count)
{
	switch (count) {
	case 0:
		fprintf(file, "0,0");
		break;
