static void set_upstreams(struct transport *transport, struct ref *refs,
	int pretend)
{
	struct ref *ref;
	for (ref = refs; ref; ref = ref->next) {
		const char *localname;
		const char *tmp;
		const char *remotename;
		unsigned char sha[20];
		int flag = 0;
		/*
		 * Check suitability for tracking. Must be successful /
		 * already up-to-date ref create/modify (not delete).
		 */
		if (ref->status != REF_STATUS_OK &&
			ref->status != REF_STATUS_UPTODATE)
			continue;
		if (!ref->peer_ref)
			continue;
		if (is_null_oid(&ref->new_oid))
			continue;

		/* Follow symbolic refs (mainly for HEAD). */
		localname = ref->peer_ref->name;
		remotename = ref->name;
		tmp = resolve_ref_unsafe(localname, RESOLVE_REF_READING,
					 sha, &flag);
		if (tmp && flag & REF_ISSYMREF &&
			starts_with(tmp, "refs/heads/"))
			localname = tmp;

		/* Both source and destination must be local branches. */
		if (!localname || !starts_with(localname, "refs/heads/"))
			continue;
		if (!remotename || !starts_with(remotename, "refs/heads/"))
			continue;

		if (!pretend)
			install_branch_config(BRANCH_CONFIG_VERBOSE,
				localname + 11, transport->remote->name,
				remotename);
		else
			printf("Would set upstream of '%s' to '%s' of '%s'\n",
				localname + 11, remotename + 11,
				transport->remote->name);
	}
}