static void get_cvs_excludes(uint32 rflags)
{
	static int initialized = 0;
	char *p, fname[MAXPATHLEN];

	if (initialized)
		return;
	initialized = 1;

	parse_filter_str(&cvs_filter_list, default_cvsignore,
			 rule_template(rflags | (protocol_version >= 30 ? FILTRULE_PERISHABLE : 0)),
			 0);

	p = module_id >= 0 && lp_use_chroot(module_id) ? "/" : getenv("HOME");
	if (p && pathjoin(fname, MAXPATHLEN, p, ".cvsignore") < MAXPATHLEN)
		parse_filter_file(&cvs_filter_list, fname, rule_template(rflags), 0);

	parse_filter_str(&cvs_filter_list, getenv("CVSIGNORE"), rule_template(rflags), 0);
}