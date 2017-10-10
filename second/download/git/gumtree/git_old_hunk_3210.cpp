	struct utsname uts;

	if (sb.len)
		return sb.buf;
	if (uname(&uts) < 0)
		die_errno(_("failed to get kernel name and information"));
	strbuf_addf(&sb, "Location %s, system %s %s %s", get_git_work_tree(),
		    uts.sysname, uts.release, uts.version);
	return sb.buf;
}

static int ident_in_untracked(const struct untracked_cache *uc)
{
	const char *end = uc->ident.buf + uc->ident.len;
	const char *p   = uc->ident.buf;

	for (p = uc->ident.buf; p < end; p += strlen(p) + 1)
		if (!strcmp(p, get_ident_string()))
			return 1;
	return 0;
}

void add_untracked_ident(struct untracked_cache *uc)
{
	if (ident_in_untracked(uc))
		return;
	strbuf_addstr(&uc->ident, get_ident_string());
	/* this strbuf contains a list of strings, save NUL too */
	strbuf_addch(&uc->ident, 0);
}

static struct untracked_cache_dir *validate_untracked_cache(struct dir_struct *dir,
						      int base_len,
						      const struct pathspec *pathspec)
{
	struct untracked_cache_dir *root;

