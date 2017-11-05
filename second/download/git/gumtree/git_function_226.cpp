static int add_one_reference(struct string_list_item *item, void *cb_data)
{
	char *ref_git;
	const char *repo;
	struct strbuf alternate = STRBUF_INIT;

	/* Beware: read_gitfile(), real_path() and mkpath() return static buffer */
	ref_git = xstrdup(real_path(item->string));

	repo = read_gitfile(ref_git);
	if (!repo)
		repo = read_gitfile(mkpath("%s/.git", ref_git));
	if (repo) {
		free(ref_git);
		ref_git = xstrdup(repo);
	}

	if (!repo && is_directory(mkpath("%s/.git/objects", ref_git))) {
		char *ref_git_git = mkpathdup("%s/.git", ref_git);
		free(ref_git);
		ref_git = ref_git_git;
	} else if (!is_directory(mkpath("%s/objects", ref_git))) {
		struct strbuf sb = STRBUF_INIT;
		if (get_common_dir(&sb, ref_git))
			die(_("reference repository '%s' as a linked checkout is not supported yet."),
			    item->string);
		die(_("reference repository '%s' is not a local repository."),
		    item->string);
	}

	if (!access(mkpath("%s/shallow", ref_git), F_OK))
		die(_("reference repository '%s' is shallow"), item->string);

	if (!access(mkpath("%s/info/grafts", ref_git), F_OK))
		die(_("reference repository '%s' is grafted"), item->string);

	strbuf_addf(&alternate, "%s/objects", ref_git);
	add_to_alternates_file(alternate.buf);
	strbuf_release(&alternate);
	free(ref_git);
	return 0;
}