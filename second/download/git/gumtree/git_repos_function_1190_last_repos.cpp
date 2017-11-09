int repo_submodule_init(struct repository *submodule,
			struct repository *superproject,
			const char *path)
{
	const struct submodule *sub;
	struct strbuf gitdir = STRBUF_INIT;
	struct strbuf worktree = STRBUF_INIT;
	int ret = 0;

	sub = submodule_from_cache(superproject, null_sha1, path);
	if (!sub) {
		ret = -1;
		goto out;
	}

	strbuf_repo_worktree_path(&gitdir, superproject, "%s/.git", path);
	strbuf_repo_worktree_path(&worktree, superproject, "%s", path);

	if (repo_init(submodule, gitdir.buf, worktree.buf)) {
		/*
		 * If initilization fails then it may be due to the submodule
		 * not being populated in the superproject's worktree.  Instead
		 * we can try to initilize the submodule by finding it's gitdir
		 * in the superproject's 'modules' directory.  In this case the
		 * submodule would not have a worktree.
		 */
		strbuf_reset(&gitdir);
		strbuf_repo_git_path(&gitdir, superproject,
				     "modules/%s", sub->name);

		if (repo_init(submodule, gitdir.buf, NULL)) {
			ret = -1;
			goto out;
		}
	}

	submodule->submodule_prefix = xstrfmt("%s%s/",
					      superproject->submodule_prefix ?
					      superproject->submodule_prefix :
					      "", path);

out:
	strbuf_release(&gitdir);
	strbuf_release(&worktree);
	return ret;
}