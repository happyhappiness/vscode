	/*
	 * If the heads to pull were given, we should have consumed
	 * all of them by matching the remote.  Otherwise, 'git fetch
	 * remote no-such-ref' would silently succeed without issuing
	 * an error.
	 */
	for (i = 0; i < nr_sought; i++) {
		if (!sought[i] || sought[i]->matched)
			continue;
		error("no such remote ref %s", sought[i]->name);
		ret = 1;
	}

	while (ref) {
		printf("%s %s\n",
		       oid_to_hex(&ref->old_oid), ref->name);
		ref = ref->next;
	}
