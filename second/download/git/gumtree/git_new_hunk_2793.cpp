	strbuf_release(&value);
}

static void dissociate_from_references(void)
{
	static const char* argv[] = { "repack", "-a", "-d", NULL };
	char *alternates = git_pathdup("objects/info/alternates");

	if (!access(alternates, F_OK)) {
		if (run_command_v_opt(argv, RUN_GIT_CMD|RUN_COMMAND_NO_STDIN))
			die(_("cannot repack to clean up"));
		if (unlink(alternates) && errno != ENOENT)
			die_errno(_("cannot unlink temporary alternates file"));
	}
	free(alternates);
}

int cmd_clone(int argc, const char **argv, const char *prefix)
{
	int is_bundle = 0, is_local;
	struct stat buf;
