{
	static struct strbuf sb = STRBUF_INIT;
	struct utsname uts;

	if (sb.len)
		return sb.buf;
	if (uname(&uts))
		die_errno(_("failed to get kernel name and information"));
	strbuf_addf(&sb, "Location %s, system %s %s %s", get_git_work_tree(),
		    uts.sysname, uts.release, uts.version);
	return sb.buf;
}

