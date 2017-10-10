	for (i = 0; i < ARRAY_SIZE(diff_temp); i++)
		if (!diff_temp[i].name)
			return diff_temp + i;
	die("BUG: diff is failing to clean up its tempfiles");
}

static void remove_tempfile(void)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(diff_temp); i++) {
		if (is_tempfile_active(&diff_temp[i].tempfile))
			delete_tempfile(&diff_temp[i].tempfile);
		diff_temp[i].name = NULL;
	}
}

static void print_line_count(FILE *file, int count)
{
	switch (count) {
	case 0:
		fprintf(file, "0,0");
		break;
