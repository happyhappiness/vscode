static void setup_git_env(void)
{
	struct strbuf sb = STRBUF_INIT;
	const char *gitfile;
	const char *shallow_file;
	const char *replace_ref_base;

	git_dir = getenv(GIT_DIR_ENVIRONMENT);
	if (!git_dir)
		git_dir = DEFAULT_GIT_DIR_ENVIRONMENT;
	gitfile = read_gitfile(git_dir);
	git_dir = xstrdup(gitfile ? gitfile : git_dir);
	if (get_common_dir(&sb, git_dir))
		git_common_dir_env = 1;
	git_common_dir = strbuf_detach(&sb, NULL);
	git_object_dir = git_path_from_env(DB_ENVIRONMENT, git_common_dir,
					   "objects", &git_db_env);
	git_index_file = git_path_from_env(INDEX_ENVIRONMENT, git_dir,
					   "index", &git_index_env);
	git_graft_file = git_path_from_env(GRAFT_ENVIRONMENT, git_common_dir,
					   "info/grafts", &git_graft_env);
	if (getenv(NO_REPLACE_OBJECTS_ENVIRONMENT))
		check_replace_refs = 0;
	replace_ref_base = getenv(GIT_REPLACE_REF_BASE_ENVIRONMENT);
	git_replace_ref_base = xstrdup(replace_ref_base ? replace_ref_base
							  : "refs/replace/");
	namespace = expand_namespace(getenv(GIT_NAMESPACE_ENVIRONMENT));
	namespace_len = strlen(namespace);
	shallow_file = getenv(GIT_SHALLOW_FILE_ENVIRONMENT);
	if (shallow_file)
		set_alternate_shallow_file(shallow_file, 0);
}