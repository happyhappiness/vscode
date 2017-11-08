static void prepare_move_submodule(const char *src, int first,
				   const char **submodule_gitfile)
{
	struct strbuf submodule_dotgit = STRBUF_INIT;
	if (!S_ISGITLINK(active_cache[first]->ce_mode))
		die(_("Directory %s is in index and no submodule?"), src);
	if (!is_staging_gitmodules_ok())
		die(_("Please stage your changes to .gitmodules or stash them to proceed"));
	strbuf_addf(&submodule_dotgit, "%s/.git", src);
	*submodule_gitfile = read_gitfile(submodule_dotgit.buf);
	if (*submodule_gitfile)
		*submodule_gitfile = xstrdup(*submodule_gitfile);
	else
		*submodule_gitfile = SUBMODULE_WITH_GITDIR;
	strbuf_release(&submodule_dotgit);
}