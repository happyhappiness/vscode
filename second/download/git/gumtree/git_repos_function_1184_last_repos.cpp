static void repo_setup_env(struct repository *repo)
{
	struct strbuf sb = STRBUF_INIT;

	repo->different_commondir = find_common_dir(&sb, repo->gitdir,
						    !repo->ignore_env);
	repo->commondir = strbuf_detach(&sb, NULL);
	repo->objectdir = git_path_from_env(DB_ENVIRONMENT, repo->commondir,
					    "objects", !repo->ignore_env);
	repo->graft_file = git_path_from_env(GRAFT_ENVIRONMENT, repo->commondir,
					     "info/grafts", !repo->ignore_env);
	repo->index_file = git_path_from_env(INDEX_ENVIRONMENT, repo->gitdir,
					     "index", !repo->ignore_env);
}