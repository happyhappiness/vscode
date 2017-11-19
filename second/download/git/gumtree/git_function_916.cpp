static int report_last_gc_error(void)
{
	struct strbuf sb = STRBUF_INIT;
	int ret;

	ret = strbuf_read_file(&sb, git_path("gc.log"), 0);
	if (ret > 0)
		return error(_("The last gc run reported the following. "
			       "Please correct the root cause\n"
			       "and remove %s.\n"
			       "Automatic cleanup will not be performed "
			       "until the file is removed.\n\n"
			       "%s"),
			     git_path("gc.log"), sb.buf);
	strbuf_release(&sb);
	return 0;
}