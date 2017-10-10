		ignore_add_errors = git_config_bool(var, value);
		return 0;
	}
	return git_default_config(var, value, cb);
}

static const char embedded_advice[] = N_(
"You've added another git repository inside your current repository.\n"
"Clones of the outer repository will not contain the contents of\n"
"the embedded repository and will not know how to obtain it.\n"
"If you meant to add a submodule, use:\n"
"\n"
"	git submodule add <url> %s\n"
"\n"
"If you added this path by mistake, you can remove it from the\n"
"index with:\n"
"\n"
"	git rm --cached %s\n"
"\n"
"See \"git help submodule\" for more information."
);

static void check_embedded_repo(const char *path)
{
	struct strbuf name = STRBUF_INIT;

	if (!warn_on_embedded_repo)
		return;
	if (!ends_with(path, "/"))
		return;

	/* Drop trailing slash for aesthetics */
	strbuf_addstr(&name, path);
	strbuf_strip_suffix(&name, "/");

	warning(_("adding embedded git repository: %s"), name.buf);
	if (advice_add_embedded_repo) {
		advise(embedded_advice, name.buf, name.buf);
		/* there may be multiple entries; advise only once */
		advice_add_embedded_repo = 0;
	}

	strbuf_release(&name);
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

	for (i = 0; i < dir->nr; i++) {
		check_embedded_repo(dir->entries[i]->name);
		if (add_file_to_index(&the_index, dir->entries[i]->name, flags)) {
			if (!ignore_add_errors)
				die(_("adding files failed"));
			exit_status = 1;
		}
	}
	return exit_status;
}

int cmd_add(int argc, const char **argv, const char *prefix)
{
	int exit_status = 0;
