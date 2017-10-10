		rc = 0;
		goto cleanup;
	}

	new_refs = 0;
	for (ref = remote_refs; ref; ref = ref->next) {
		struct argv_array commit_argv = ARGV_ARRAY_INIT;

		if (!ref->peer_ref)
			continue;

		if (is_null_oid(&ref->peer_ref->new_oid)) {
			if (delete_remote_branch(ref->name, 1) == -1) {
				error("Could not remove %s", ref->name);
				if (helper_status)
					printf("error %s cannot remove\n", ref->name);
				rc = -4;
			}
			else if (helper_status)
				printf("ok %s\n", ref->name);
			new_refs++;
			continue;
		}

		if (!oidcmp(&ref->old_oid, &ref->peer_ref->new_oid)) {
			if (push_verbosely)
				fprintf(stderr, "'%s': up-to-date\n", ref->name);
			if (helper_status)
				printf("ok %s up to date\n", ref->name);
			continue;
		}

		if (!force_all &&
		    !is_null_oid(&ref->old_oid) &&
		    !ref->force) {
			if (!has_object_file(&ref->old_oid) ||
			    !ref_newer(&ref->peer_ref->new_oid,
				       &ref->old_oid)) {
				/*
				 * We do not have the remote ref, or
				 * we know that the remote ref is not
				 * an ancestor of what we are trying to
				 * push.  Either way this can be losing
				 * commits at the remote end and likely
