static void reject_updates_to_hidden(struct command *commands)
{
	struct strbuf refname_full = STRBUF_INIT;
	size_t prefix_len;
	struct command *cmd;

	strbuf_addstr(&refname_full, get_git_namespace());
	prefix_len = refname_full.len;

	for (cmd = commands; cmd; cmd = cmd->next) {
		if (cmd->error_string)
			continue;

		strbuf_setlen(&refname_full, prefix_len);
		strbuf_addstr(&refname_full, cmd->ref_name);

		if (!ref_is_hidden(cmd->ref_name, refname_full.buf))
			continue;
		if (is_null_oid(&cmd->new_oid))
			cmd->error_string = "deny deleting a hidden ref";
		else
			cmd->error_string = "deny updating a hidden ref";
	}

	strbuf_release(&refname_full);
}