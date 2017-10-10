			printf(get_shared_repository()
			       ? _("Initialized empty shared Git repository in %s%s\n")
			       : _("Initialized empty Git repository in %s%s\n"),
			       git_dir, len && git_dir[len-1] != '/' ? "/" : "");
	}

	free(original_git_dir);
	return 0;
}

static int guess_repository_type(const char *git_dir)
{
	const char *slash;
