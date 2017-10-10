	/*
	 * If the heads to pull were given, we should have consumed
	 * all of them by matching the remote.  Otherwise, 'git fetch
	 * remote no-such-ref' would silently succeed without issuing
	 * an error.
	 */
	ret |= report_unmatched_refs(sought, nr_sought);

	while (ref) {
		printf("%s %s\n",
		       oid_to_hex(&ref->old_oid), ref->name);
		ref = ref->next;
	}
