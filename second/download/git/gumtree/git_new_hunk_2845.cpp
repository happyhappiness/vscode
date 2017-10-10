		fprintf(stderr, "From %s\n", *remote->url);
	for ( ; ref; ref = ref->next) {
		if (!check_ref_type(ref, flags))
			continue;
		if (!tail_match(pattern, ref->name))
			continue;
		printf("%s	%s\n", oid_to_hex(&ref->old_oid), ref->name);
		status = 0; /* we found something */
	}
	return status;
}
