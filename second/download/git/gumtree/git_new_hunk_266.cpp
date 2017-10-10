		ignore_add_errors = git_config_bool(var, value);
		return 0;
	}
	return git_default_config(var, value, cb);
}

static int add_files(struct dir_struct *dir, int flags)
{
	int i, exit_status = 0;

	if (dir->ignored_nr) {
		fprintf(stderr, _(ignore_error));
		for (i = 0; i < dir->ignored_nr; i++)
			fprintf(stderr, "%s\n", dir->ignored[i]->name);
		fprintf(stderr, _("Use -f if you really want to add them.\n"));
		exit_status = 1;
	}

	for (i = 0; i < dir->nr; i++)
		if (add_file_to_index(&the_index, dir->entries[i]->name, flags)) {
			if (!ignore_add_errors)
				die(_("adding files failed"));
			exit_status = 1;
		}
	return exit_status;
}

int cmd_add(int argc, const char **argv, const char *prefix)
{
	int exit_status = 0;
	struct pathspec pathspec;
	struct dir_struct dir;
	int flags;
	int add_new_files;
	int require_pathspec;
	char *seen = NULL;

	git_config(add_config, NULL);

