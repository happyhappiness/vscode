static int split_maildir(const char *maildir, const char *dir,
	int nr_prec, int skip)
{
	char file[PATH_MAX];
	char name[PATH_MAX];
	int ret = -1;
	int i;
	struct string_list list = STRING_LIST_INIT_DUP;

	list.cmp = maildir_filename_cmp;

	if (populate_maildir_list(&list, maildir) < 0)
		goto out;

	for (i = 0; i < list.nr; i++) {
		FILE *f;
		snprintf(file, sizeof(file), "%s/%s", maildir, list.items[i].string);
		f = fopen(file, "r");
		if (!f) {
			error("cannot open mail %s (%s)", file, strerror(errno));
			goto out;
		}

		if (strbuf_getwholeline(&buf, f, '\n')) {
			error("cannot read mail %s (%s)", file, strerror(errno));
			goto out;
		}

		sprintf(name, "%s/%0*d", dir, nr_prec, ++skip);
		split_one(f, name, 1);

		fclose(f);
	}

	ret = skip;
out:
	string_list_clear(&list, 1);
	return ret;
}