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

