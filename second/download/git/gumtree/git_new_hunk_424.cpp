	for (i = 0; i < list.nr; i++) {
		const struct cache_entry *ce = list.entries[i];

		if (ce_stage(ce))
			printf("%06o %s U\t", ce->ce_mode, sha1_to_hex(null_sha1));
		else
			printf("%06o %s %d\t", ce->ce_mode,
			       oid_to_hex(&ce->oid), ce_stage(ce));

		utf8_fprintf(stdout, "%s\n", ce->name);
	}
	return 0;
}

