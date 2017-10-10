}

static int resolve_relative_path(int argc, const char **argv, const char *prefix)
{
	struct strbuf sb = STRBUF_INIT;
	if (argc != 3)
		die("submodule--helper relative-path takes exactly 2 arguments, got %d", argc);

	printf("%s", relative_path(argv[1], argv[2], &sb));
	strbuf_release(&sb);
	return 0;
}

static const char *remote_submodule_branch(const char *path)
{
	const struct submodule *sub;
	gitmodules_config();
	git_config(submodule_config, NULL);

	sub = submodule_from_path(null_sha1, path);
	if (!sub)
		return NULL;

	if (!sub->branch)
		return "master";

	if (!strcmp(sub->branch, ".")) {
		unsigned char sha1[20];
		const char *refname = resolve_ref_unsafe("HEAD", 0, sha1, NULL);

		if (!refname)
			die(_("No such ref: %s"), "HEAD");

		/* detached HEAD */
		if (!strcmp(refname, "HEAD"))
			die(_("Submodule (%s) branch configured to inherit "
			      "branch from superproject, but the superproject "
			      "is not on any branch"), sub->name);

		if (!skip_prefix(refname, "refs/heads/", &refname))
			die(_("Expecting a full ref name, got %s"), refname);
		return refname;
	}

	return sub->branch;
}

static int resolve_remote_submodule_branch(int argc, const char **argv,
		const char *prefix)
{
	const char *ret;
	struct strbuf sb = STRBUF_INIT;
	if (argc != 2)
		die("submodule--helper remote-branch takes exactly one arguments, got %d", argc);

	ret = remote_submodule_branch(argv[1]);
	if (!ret)
		die("submodule %s doesn't exist", argv[1]);

	printf("%s", ret);
	strbuf_release(&sb);
	return 0;
}

struct cmd_struct {
	const char *cmd;
	int (*fn)(int, const char **, const char *);
};

static struct cmd_struct commands[] = {
