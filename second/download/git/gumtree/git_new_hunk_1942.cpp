
	if (dir->ignored_nr) {
		fprintf(stderr, _(ignore_error));
		for (i = 0; i < dir->ignored_nr; i++)
			fprintf(stderr, "%s\n", dir->ignored[i]->name);
		fprintf(stderr, _("Use -f if you really want to add them.\n"));
		exit_status = 1;
	}

	for (i = 0; i < dir->nr; i++)
		if (add_file_to_cache(dir->entries[i]->name, flags)) {
			if (!ignore_add_errors)
				die(_("adding files failed"));
