static void update_shallow_info(struct command *commands,
				struct shallow_info *si,
				struct oid_array *ref)
{
	struct command *cmd;
	int *ref_status;
	remove_nonexistent_theirs_shallow(si);
	if (!si->nr_ours && !si->nr_theirs) {
		shallow_update = 0;
		return;
	}

	for (cmd = commands; cmd; cmd = cmd->next) {
		if (is_null_oid(&cmd->new_oid))
			continue;
		oid_array_append(ref, &cmd->new_oid);
		cmd->index = ref->nr - 1;
	}
	si->ref = ref;

	if (shallow_update) {
		prepare_shallow_update(commands, si);
		return;
	}

	ALLOC_ARRAY(ref_status, ref->nr);
	assign_shallow_commits_to_refs(si, NULL, ref_status);
	for (cmd = commands; cmd; cmd = cmd->next) {
		if (is_null_oid(&cmd->new_oid))
			continue;
		if (ref_status[cmd->index]) {
			cmd->error_string = "shallow update not allowed";
			cmd->skip_update = 1;
		}
	}
	free(ref_status);
}