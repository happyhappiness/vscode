static void remove_tempfile(void)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(diff_temp); i++) {
		if (is_tempfile_active(&diff_temp[i].tempfile))
			delete_tempfile(&diff_temp[i].tempfile);
		diff_temp[i].name = NULL;
	}
}