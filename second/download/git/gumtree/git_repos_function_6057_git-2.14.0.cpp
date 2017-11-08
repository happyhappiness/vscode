static NORETURN void exit_cleanup(const char *tmpdir, int exit_code)
{
	struct strbuf buf = STRBUF_INIT;
	strbuf_addstr(&buf, tmpdir);
	remove_dir_recursively(&buf, 0);
	if (exit_code)
		warning(_("failed: %d"), exit_code);
	exit(exit_code);
}