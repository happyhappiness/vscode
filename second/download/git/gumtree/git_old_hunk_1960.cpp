	}

	strbuf_release(&key);
	strbuf_release(&value);
}

int cmd_clone(int argc, const char **argv, const char *prefix)
{
	int is_bundle = 0, is_local;
	struct stat buf;
	const char *repo_name, *repo, *work_tree, *git_dir;
	char *path, *dir;
