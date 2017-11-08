static void ls_from_active_commit(const char *path)
{
	/* ls "path/to/file" */
	printf("ls \"");
	quote_c_style(path, NULL, stdout, 1);
	printf("\"\n");
	fflush(stdout);
}