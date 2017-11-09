static int check_ref_format_branch(const char *arg)
{
	struct strbuf sb = STRBUF_INIT;
	int nongit;

	setup_git_directory_gently(&nongit);
	if (strbuf_check_branch_ref(&sb, arg))
		die("'%s' is not a valid branch name", arg);
	printf("%s\n", sb.buf + 11);
	return 0;
}