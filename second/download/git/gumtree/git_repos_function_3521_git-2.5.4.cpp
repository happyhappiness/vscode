static void read_remotes_file(struct remote *remote)
{
	FILE *f = fopen(git_path("remotes/%s", remote->name), "r");

	if (!f)
		return;
	remote->origin = REMOTE_REMOTES;
	while (fgets(buffer, BUF_SIZE, f)) {
		int value_list;
		char *s, *p;

		if (starts_with(buffer, "URL:")) {
			value_list = 0;
			s = buffer + 4;
		} else if (starts_with(buffer, "Push:")) {
			value_list = 1;
			s = buffer + 5;
		} else if (starts_with(buffer, "Pull:")) {
			value_list = 2;
			s = buffer + 5;
		} else
			continue;

		while (isspace(*s))
			s++;
		if (!*s)
			continue;

		p = s + strlen(s);
		while (isspace(p[-1]))
			*--p = 0;

		switch (value_list) {
		case 0:
			add_url_alias(remote, xstrdup(s));
			break;
		case 1:
			add_push_refspec(remote, xstrdup(s));
			break;
		case 2:
			add_fetch_refspec(remote, xstrdup(s));
			break;
		}
	}
	fclose(f);
}