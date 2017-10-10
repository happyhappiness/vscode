	return (unsigned char)*a - (unsigned char)*b;
}

static int split_maildir(const char *maildir, const char *dir,
	int nr_prec, int skip)
{
	char *file = NULL;
	FILE *f = NULL;
	int ret = -1;
	int i;
	struct string_list list = STRING_LIST_INIT_DUP;

	list.cmp = maildir_filename_cmp;

	if (populate_maildir_list(&list, maildir) < 0)
		goto out;

	for (i = 0; i < list.nr; i++) {
		char *name;

		free(file);
		file = xstrfmt("%s/%s", maildir, list.items[i].string);

		f = fopen(file, "r");
		if (!f) {
			error("cannot open mail %s (%s)", file, strerror(errno));
			goto out;
		}

		if (strbuf_getwholeline(&buf, f, '\n')) {
			error("cannot read mail %s (%s)", file, strerror(errno));
			goto out;
		}

		name = xstrfmt("%s/%0*d", dir, nr_prec, ++skip);
		split_one(f, name, 1);
		free(name);

		fclose(f);
		f = NULL;
	}

	ret = skip;
out:
	if (f)
		fclose(f);
	free(file);
	string_list_clear(&list, 1);
	return ret;
}

static int split_mbox(const char *file, const char *dir, int allow_bare,
		      int nr_prec, int skip)
{
	int ret = -1;
	int peek;

	FILE *f = !strcmp(file, "-") ? stdin : fopen(file, "r");
	int file_done = 0;

