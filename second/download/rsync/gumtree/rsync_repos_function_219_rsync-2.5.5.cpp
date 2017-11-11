int cmp_modtime(time_t file1, time_t file2)
{
	extern int modify_window;

	if (file2 > file1) {
		if (file2 - file1 <= modify_window) return 0;
		return -1;
	}
	if (file1 - file2 <= modify_window) return 0;
	return 1;
}