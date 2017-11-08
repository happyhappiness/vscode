static int get_sha1_oneline(const char *prefix, unsigned char *sha1,
			    struct commit_list *list)
{
	struct commit_list *backup = NULL, *l;
	int found = 0;
	regex_t regex;

	if (prefix[0] == '!') {
		if (prefix[1] != '!')
			die ("Invalid search pattern: %s", prefix);
		prefix++;
	}

	if (regcomp(&regex, prefix, REG_EXTENDED))
		die("Invalid search pattern: %s", prefix);

	for (l = list; l; l = l->next) {
		l->item->object.flags |= ONELINE_SEEN;
		commit_list_insert(l->item, &backup);
	}
	while (list) {
		const char *p, *buf;
		struct commit *commit;
		int matches;

		commit = pop_most_recent_commit(&list, ONELINE_SEEN);
		if (!parse_object(commit->object.oid.hash))
			continue;
		buf = get_commit_buffer(commit, NULL);
		p = strstr(buf, "\n\n");
		matches = p && !regexec(&regex, p + 2, 0, NULL, 0);
		unuse_commit_buffer(commit, buf);

		if (matches) {
			hashcpy(sha1, commit->object.oid.hash);
			found = 1;
			break;
		}
	}
	regfree(&regex);
	free_commit_list(list);
	for (l = backup; l; l = l->next)
		clear_commit_marks(l->item, ONELINE_SEEN);
	free_commit_list(backup);
	return found ? 0 : -1;
}