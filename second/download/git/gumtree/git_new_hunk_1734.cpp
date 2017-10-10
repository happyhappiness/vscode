	return path;
}

static struct lock_file lock_file;
#define SUBMODULE_WITH_GITDIR ((const char *)1)

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

static int index_range_of_same_dir(const char *src, int length,
				   int *first_p, int *last_p)
{
	const char *src_w_slash = add_slash(src);
	int first, last, len_w_slash = length + 1;

	first = cache_name_pos(src_w_slash, len_w_slash);
	if (first >= 0)
		die(_("%.*s is in index"), len_w_slash, src_w_slash);

	first = -1 - first;
	for (last = first; last < active_nr; last++) {
		const char *path = active_cache[last]->name;
		if (strncmp(path, src_w_slash, len_w_slash))
			break;
	}
	if (src_w_slash != src)
		free((char *)src_w_slash);
	*first_p = first;
	*last_p = last;
	return last - first;
}

int cmd_mv(int argc, const char **argv, const char *prefix)
{
	int i, gitmodules_modified = 0;
	int verbose = 0, show_only = 0, force = 0, ignore_errors = 0;
	struct option builtin_mv_options[] = {
		OPT__VERBOSE(&verbose, N_("be verbose")),
