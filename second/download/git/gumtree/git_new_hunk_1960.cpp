	}

	strbuf_release(&key);
	strbuf_release(&value);
}

static void dissociate_from_references(void)
{
	static const char* argv[] = { "repack", "-a", "-d", NULL };

	if (run_command_v_opt(argv, RUN_GIT_CMD|RUN_COMMAND_NO_STDIN))
		die(_("cannot repack to clean up"));
	if (unlink(git_path("objects/info/alternates")) && errno != ENOENT)
		die_errno(_("cannot unlink temporary alternates file"));
}

int cmd_clone(int argc, const char **argv, const char *prefix)
{
	int is_bundle = 0, is_local;
	struct stat buf;
	const char *repo_name, *repo, *work_tree, *git_dir;
	char *path, *dir;
