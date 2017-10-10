	if (check_refname_format(buf.buf, 0))
		die("bad git namespace path \"%s\"", raw_namespace);
	strbuf_addch(&buf, '/');
	return strbuf_detach(&buf, NULL);
}

static void setup_git_env(void)
{
	const char *gitfile;
	const char *shallow_file;

	git_dir = getenv(GIT_DIR_ENVIRONMENT);
	if (!git_dir)
		git_dir = DEFAULT_GIT_DIR_ENVIRONMENT;
	gitfile = read_gitfile(git_dir);
	git_dir = xstrdup(gitfile ? gitfile : git_dir);
	git_object_dir = getenv(DB_ENVIRONMENT);
	if (!git_object_dir) {
		git_object_dir = xmalloc(strlen(git_dir) + 9);
		sprintf(git_object_dir, "%s/objects", git_dir);
	}
	git_index_file = getenv(INDEX_ENVIRONMENT);
	if (!git_index_file) {
		git_index_file = xmalloc(strlen(git_dir) + 7);
		sprintf(git_index_file, "%s/index", git_dir);
	}
	git_graft_file = getenv(GRAFT_ENVIRONMENT);
	if (!git_graft_file)
		git_graft_file = git_pathdup("info/grafts");
	if (getenv(NO_REPLACE_OBJECTS_ENVIRONMENT))
		check_replace_refs = 0;
	namespace = expand_namespace(getenv(GIT_NAMESPACE_ENVIRONMENT));
	namespace_len = strlen(namespace);
	shallow_file = getenv(GIT_SHALLOW_FILE_ENVIRONMENT);
	if (shallow_file)
