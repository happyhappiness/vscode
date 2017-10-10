		}

	*olen = len;
	return name;
}

static int add_worktree(const char *path, const char **child_argv)
{
	struct strbuf sb_git = STRBUF_INIT, sb_repo = STRBUF_INIT;
	struct strbuf sb = STRBUF_INIT;
	const char *name;
	struct stat st;
	struct child_process cp;
	int counter = 0, len, ret;
	unsigned char rev[20];

	if (file_exists(path) && !is_empty_dir(path))
		die(_("'%s' already exists"), path);

	name = worktree_basename(path, &len);
	strbuf_addstr(&sb_repo,
		      git_path("worktrees/%.*s", (int)(path + len - name), name));
	len = sb_repo.len;
	if (safe_create_leading_directories_const(sb_repo.buf))
		die_errno(_("could not create leading directories of '%s'"),
