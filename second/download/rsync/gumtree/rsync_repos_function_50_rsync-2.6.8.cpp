static void get_cvs_excludes(uint32 mflags)
{
	char *p, fname[MAXPATHLEN];
	static int initialized = 0;

	if (initialized)
		return;
	initialized = 1;

	parse_rule(&cvs_filter_list, default_cvsignore, mflags, 0);

	p = module_id >= 0 && lp_use_chroot(module_id) ? "/" : getenv("HOME");
	if (p && pathjoin(fname, MAXPATHLEN, p, ".cvsignore") < MAXPATHLEN)
		parse_filter_file(&cvs_filter_list, fname, mflags, 0);

	parse_rule(&cvs_filter_list, getenv("CVSIGNORE"), mflags, 0);
}