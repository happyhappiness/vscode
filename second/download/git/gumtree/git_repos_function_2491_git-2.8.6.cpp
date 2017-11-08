static struct commit *parse_insn_line(char *bol, char *eol, struct replay_opts *opts)
{
	unsigned char commit_sha1[20];
	enum replay_action action;
	char *end_of_object_name;
	int saved, status, padding;

	if (starts_with(bol, "pick")) {
		action = REPLAY_PICK;
		bol += strlen("pick");
	} else if (starts_with(bol, "revert")) {
		action = REPLAY_REVERT;
		bol += strlen("revert");
	} else
		return NULL;

	/* Eat up extra spaces/ tabs before object name */
	padding = strspn(bol, " \t");
	if (!padding)
		return NULL;
	bol += padding;

	end_of_object_name = bol + strcspn(bol, " \t\n");
	saved = *end_of_object_name;
	*end_of_object_name = '\0';
	status = get_sha1(bol, commit_sha1);
	*end_of_object_name = saved;

	/*
	 * Verify that the action matches up with the one in
	 * opts; we don't support arbitrary instructions
	 */
	if (action != opts->action) {
		const char *action_str;
		action_str = action == REPLAY_REVERT ? "revert" : "cherry-pick";
		error(_("Cannot %s during a %s"), action_str, action_name(opts));
		return NULL;
	}

	if (status < 0)
		return NULL;

	return lookup_commit_reference(commit_sha1);
}