static void ls_from_rev(uint32_t rev, const char *path)
{
	/* ls :5 path/to/old/file */
	printf("ls :%"PRIu32" ", rev);
	quote_c_style(path, NULL, stdout, 0);
	putchar('\n');
	fflush(stdout);
}