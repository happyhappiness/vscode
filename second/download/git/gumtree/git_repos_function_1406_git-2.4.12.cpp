static void read_mailmap_line(struct string_list *map, char *buffer,
			      char **repo_abbrev)
{
	char *name1 = NULL, *email1 = NULL, *name2 = NULL, *email2 = NULL;
	if (buffer[0] == '#') {
		static const char abbrev[] = "# repo-abbrev:";
		int abblen = sizeof(abbrev) - 1;
		int len = strlen(buffer);

		if (!repo_abbrev)
			return;

		if (len && buffer[len - 1] == '\n')
			buffer[--len] = 0;
		if (!strncmp(buffer, abbrev, abblen)) {
			char *cp;

			free(*repo_abbrev);
			*repo_abbrev = xmalloc(len);

			for (cp = buffer + abblen; isspace(*cp); cp++)
				; /* nothing */
			strcpy(*repo_abbrev, cp);
		}
		return;
	}
	if ((name2 = parse_name_and_email(buffer, &name1, &email1, 0)) != NULL)
		parse_name_and_email(name2, &name2, &email2, 1);

	if (email1)
		add_mapping(map, name1, email1, name2, email2);
}