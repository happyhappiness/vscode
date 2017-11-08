static int robust_move(char *src, char *dst)
{
	if (robust_rename(src, dst, NULL, 0755) < 0
	 && (errno != ENOENT || make_bak_dir(dst) < 0
	  || robust_rename(src, dst, NULL, 0755) < 0))
		return -1;
	return 0;
}