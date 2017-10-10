	}
	path = real_path(dir);

cleanup_return:
	if (return_error_code)
		*return_error_code = error_code;
	else if (error_code)
		read_gitfile_error_die(error_code, path, dir);

	free(buf);
	return error_code ? NULL : path;
}

static const char *setup_explicit_git_dir(const char *gitdirenv,
