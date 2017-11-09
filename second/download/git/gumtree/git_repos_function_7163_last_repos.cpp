static int append_fetch_head(FILE *fp,
			     const char *head, const char *remote,
			     const char *remote_name, const char *remote_nick,
			     const char *local_name, int not_for_merge,
			     int verbose, int force)
{
	struct commit *commit;
	int remote_len, i, note_len;
	unsigned char sha1[20];
	char note[1024];
	const char *what, *kind;

	if (get_sha1(head, sha1))
		return error("Not a valid object name: %s", head);
	commit = lookup_commit_reference_gently(sha1, 1);
	if (!commit)
		not_for_merge = 1;

	if (!strcmp(remote_name, "HEAD")) {
		kind = "";
		what = "";
	}
	else if (!strncmp(remote_name, "refs/heads/", 11)) {
		kind = "branch";
		what = remote_name + 11;
	}
	else if (!strncmp(remote_name, "refs/tags/", 10)) {
		kind = "tag";
		what = remote_name + 10;
	}
	else if (!strncmp(remote_name, "refs/remotes/", 13)) {
		kind = "remote-tracking branch";
		what = remote_name + 13;
	}
	else {
		kind = "";
		what = remote_name;
	}

	remote_len = strlen(remote);
	for (i = remote_len - 1; remote[i] == '/' && 0 <= i; i--)
		;
	remote_len = i + 1;
	if (4 < i && !strncmp(".git", remote + i - 3, 4))
		remote_len = i - 3;

	note_len = 0;
	if (*what) {
		if (*kind)
			note_len += sprintf(note + note_len, "%s ", kind);
		note_len += sprintf(note + note_len, "'%s' of ", what);
	}
	note_len += sprintf(note + note_len, "%.*s", remote_len, remote);
	fprintf(fp, "%s\t%s\t%s\n",
		sha1_to_hex(commit ? commit->object.sha1 : sha1),
		not_for_merge ? "not-for-merge" : "",
		note);
	return update_local_ref(local_name, head, note, verbose, force);
}