static void remove_tempfile(void)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(diff_temp); i++) {
		if (diff_temp[i].name == diff_temp[i].tmp_path)
			unlink_or_warn(diff_temp[i].name);
		diff_temp[i].name = NULL;
	}
}