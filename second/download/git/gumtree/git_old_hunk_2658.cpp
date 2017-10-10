		strncpy(dir, path, pathlen);
		strncpy(dir + pathlen, buf + 8, len - 8);
		dir[dirlen] = '\0';
		free(buf);
		buf = dir;
	}

	if (!is_git_directory(dir))
		die("Not a git repository: %s", dir);

	update_linked_gitdir(path, dir);
	path = real_path(dir);

	free(buf);
	return path;
}

static const char *setup_explicit_git_dir(const char *gitdirenv,
					  struct strbuf *cwd,
					  int *nongit_ok)
{
