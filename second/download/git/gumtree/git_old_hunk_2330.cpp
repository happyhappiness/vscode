		free(buf);
		buf = dir;
	}

	if (!is_git_directory(dir))
		die("Not a git repository: %s", dir);
	path = real_path(dir);

	free(buf);
	return path;
}

