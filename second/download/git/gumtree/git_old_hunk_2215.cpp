			die(_("Refusing to fetch into current branch %s "
			    "of non-bare repository"), current_branch->refname);
}

static int truncate_fetch_head(void)
{
	char *filename = git_path("FETCH_HEAD");
	FILE *fp = fopen(filename, "w");

	if (!fp)
		return error(_("cannot open %s: %s\n"), filename, strerror(errno));
	fclose(fp);
	return 0;
