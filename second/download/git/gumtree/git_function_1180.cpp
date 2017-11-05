void create_branch(const char *head,
		   const char *name, const char *start_name,
		   int force, int reflog, int clobber_head,
		   int quiet, enum branch_track track)
{
	struct ref_lock *lock = NULL;
	struct commit *commit;
	unsigned char sha1[20];
	char *real_ref, msg[PATH_MAX + 20];
	struct strbuf ref = STRBUF_INIT;
	int forcing = 0;
	int dont_change_ref = 0;
	int explicit_tracking = 0;

	if (track == BRANCH_TRACK_EXPLICIT || track == BRANCH_TRACK_OVERRIDE)
		explicit_tracking = 1;

	if (validate_new_branchname(name, &ref, force,
				    track == BRANCH_TRACK_OVERRIDE ||
				    clobber_head)) {
		if (!force)
			dont_change_ref = 1;
		else
			forcing = 1;
	}

	real_ref = NULL;
	if (get_sha1(start_name, sha1)) {
		if (explicit_tracking) {
			if (advice_set_upstream_failure) {
				error(_(upstream_missing), start_name);
				advise(_(upstream_advice));
				exit(1);
			}
			die(_(upstream_missing), start_name);
		}
		die(_("Not a valid object name: '%s'."), start_name);
	}

	switch (dwim_ref(start_name, strlen(start_name), sha1, &real_ref)) {
	case 0:
		/* Not branching from any existing branch */
		if (explicit_tracking)
			die(_(upstream_not_branch), start_name);
		break;
	case 1:
		/* Unique completion -- good, only if it is a real branch */
		if (!starts_with(real_ref, "refs/heads/") &&
		    validate_remote_tracking_branch(real_ref)) {
			if (explicit_tracking)
				die(_(upstream_not_branch), start_name);
			else
				real_ref = NULL;
		}
		break;
	default:
		die(_("Ambiguous object name: '%s'."), start_name);
		break;
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