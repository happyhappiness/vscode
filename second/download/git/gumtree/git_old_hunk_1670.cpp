	}

	if ((commit = lookup_commit_reference(sha1)) == NULL)
		die(_("Not a valid branch point: '%s'."), start_name);
	hashcpy(sha1, commit->object.sha1);

	if (!dont_change_ref) {
		lock = lock_any_ref_for_update(ref.buf, NULL, 0, NULL);
		if (!lock)
			die_errno(_("Failed to lock ref for update"));
	}

	if (reflog)
		log_all_ref_updates = 1;

	if (forcing)
		snprintf(msg, sizeof msg, "branch: Reset to %s",
			 start_name);
	else if (!dont_change_ref)
		snprintf(msg, sizeof msg, "branch: Created from %s",
			 start_name);

	if (real_ref && track)
		setup_tracking(ref.buf + 11, real_ref, track, quiet);

	if (!dont_change_ref)
		if (write_ref_sha1(lock, sha1, msg) < 0)
			die_errno(_("Failed to write ref"));

	strbuf_release(&ref);
	free(real_ref);
}

void remove_branch_state(void)
{
