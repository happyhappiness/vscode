static void apply_cas(struct push_cas_option *cas,
		      struct remote *remote,
		      struct ref *ref)
{
	int i;

	/* Find an explicit --<option>=<name>[:<value>] entry */
	for (i = 0; i < cas->nr; i++) {
		struct push_cas *entry = &cas->entry[i];
		if (!refname_match(entry->refname, ref->name))
			continue;
		ref->expect_old_sha1 = 1;
		if (!entry->use_tracking)
			hashcpy(ref->old_sha1_expect, cas->entry[i].expect);
		else if (remote_tracking(remote, ref->name, ref->old_sha1_expect))
			ref->expect_old_no_trackback = 1;
		return;
	}

	/* Are we using "--<option>" to cover all? */
	if (!cas->use_tracking_for_rest)
		return;

	ref->expect_old_sha1 = 1;
	if (remote_tracking(remote, ref->name, ref->old_sha1_expect))
		ref->expect_old_no_trackback = 1;
}