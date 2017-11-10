static void read_mailmap_string(struct string_list *map, char *buf,
				char **repo_abbrev)
{
	while (*buf) {
		char *end = strchrnul(buf, '\n');

		if (*end)
			*end++ = '\0';

		read_mailmap_line(map, buf, repo_abbrev);
		buf = end;
	}
}