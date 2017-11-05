void set_ref_status_for_push(struct ref *remote_refs, int send_mirror,
			     int force_update)
{
	struct ref *ref;

	for (ref = remote_refs; ref; ref = ref->next) {
		int force_ref_update = ref->force || force_update;
		int reject_reason = 0;

		if (ref->peer_ref)
			hashcpy(ref->new_sha1, ref->peer_ref->new_sha1);
		else if (!send_mirror)
			continue;

		ref->deletion = is_null_sha1(ref->new_sha1);
		if (!ref->deletion &&
			!hashcmp(ref->old_sha1, ref->new_sha1)) {
			ref->status = REF_STATUS_UPTODATE;
			continue;
		}

		/*
		 * Bypass the usual "must fast-forward" check but
		 * replace it with a weaker "the old value must be
		 * this value we observed".  If the remote ref has
		 * moved and is now different from what we expect,
		 * reject any push.
		 *
		 * It also is an error if the user told us to check
		 * with the remote-tracking branch to find the value
		 * to expect, but we did not have such a tracking
		 * branch.
		 */
		if (ref->expect_old_sha1) {
			if (ref->expect_old_no_trackback ||
			    hashcmp(ref->old_sha1, ref->old_sha1_expect))
				reject_reason = REF_STATUS_REJECT_STALE;
		}

		/*
		 * The usual "must fast-forward" rules.
		 *
		 * Decide whether an individual refspec A:B can be
		 * pushed.  The push will succeed if any of the
		 * following are true:
		 *
		 * (1) the remote reference B does not exist
		 *
		 * (2) the remote reference B is being removed (i.e.,
		 *     pushing :B where no source is specified)
		 *
		 * (3) the destination is not under refs/tags/, and
		 *     if the old and new value is a commit, the new
		 *     is a descendant of the old.
		 *
		 * (4) it is forced using the +A:B notation, or by
		 *     passing the --force argument
		 */

		else if (!ref->deletion && !is_null_sha1(ref->old_sha1)) {
			if (starts_with(ref->name, "refs/tags/"))
				reject_reason = REF_STATUS_REJECT_ALREADY_EXISTS;
			else if (!has_sha1_file(ref->old_sha1))
				reject_reason = REF_STATUS_REJECT_FETCH_FIRST;
			else if (!lookup_commit_reference_gently(ref->old_sha1, 1) ||
				 !lookup_commit_reference_gently(ref->new_sha1, 1))
				reject_reason = REF_STATUS_REJECT_NEEDS_FORCE;
			else if (!ref_newer(ref->new_sha1, ref->old_sha1))
				reject_reason = REF_STATUS_REJECT_NONFASTFORWARD;
		}

		/*
		 * "--force" will defeat any rejection implemented
		 * by the rules above.
		 */
		if (!force_ref_update)
			ref->status = reject_reason;
		else if (reject_reason)
			ref->forced_update = 1;
	}
}