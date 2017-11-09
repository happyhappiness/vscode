int cmp_time(time_t file1, time_t file2)
{
	if (file2 > file1) {
		/* The final comparison makes sure that modify_window doesn't overflow a
		 * time_t, which would mean that file2 must be in the equality window. */
		if (!modify_window || (file2 > file1 + modify_window && file1 + modify_window > file1))
			return -1;
	} else if (file1 > file2) {
		if (!modify_window || (file1 > file2 + modify_window && file2 + modify_window > file2))
			return 1;
	}
	return 0;
}