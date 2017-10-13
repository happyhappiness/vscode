static struct packed_ref_cache *read_packed_refs(const char *packed_refs_file)
{
	FILE *f;
	struct packed_ref_cache *packed_refs = xcalloc(1, sizeof(*packed_refs));
	struct ref_entry *last = NULL;
	struct strbuf line = STRBUF_INIT;
	enum { PEELED_NONE, PEELED_TAGS, PEELED_FULLY } peeled = PEELED_NONE;
	struct ref_dir *dir;

	acquire_packed_ref_cache(packed_refs);
	packed_refs->cache = create_ref_cache(NULL, NULL);
	packed_refs->cache->root->flag &= ~REF_INCOMPLETE;

	f = fopen(packed_refs_file, "r");
	if (!f) {
		if (errno == ENOENT) {
			/*
			 * This is OK; it just means that no
			 * "packed-refs" file has been written yet,
			 * which is equivalent to it being empty.
			 */
			return packed_refs;
		} else {
			die_errno("couldn't read %s", packed_refs_file);
		}
	}

	stat_validity_update(&packed_refs->validity, fileno(f));

	dir = get_ref_dir(packed_refs->cache->root);
	while (strbuf_getwholeline(&line, f, '\n') != EOF) {
		struct object_id oid;
		const char *refname;
		const char *traits;

		if (skip_prefix(line.buf, "# pack-refs with:", &traits)) {
			if (strstr(traits, " fully-peeled "))
				peeled = PEELED_FULLY;
			else if (strstr(traits, " peeled "))
				peeled = PEELED_TAGS;
			/* perhaps other traits later as well */
			continue;
		}

		refname = parse_ref_line(&line, &oid);
		if (refname) {
			int flag = REF_ISPACKED;

			if (check_refname_format(refname, REFNAME_ALLOW_ONELEVEL)) {
				if (!refname_is_safe(refname))
					die("packed refname is dangerous: %s", refname);
				oidclr(&oid);
				flag |= REF_BAD_NAME | REF_ISBROKEN;
			}
			last = create_ref_entry(refname, &oid, flag);
			if (peeled == PEELED_FULLY ||
			    (peeled == PEELED_TAGS && starts_with(refname, "refs/tags/")))
				last->flag |= REF_KNOWS_PEELED;
			add_ref_entry(dir, last);
			continue;
		}
		if (last &&
		    line.buf[0] == '^' &&
		    line.len == PEELED_LINE_LENGTH &&
		    line.buf[PEELED_LINE_LENGTH - 1] == '\n' &&
		    !get_oid_hex(line.buf + 1, &oid)) {
			oidcpy(&last->u.value.peeled, &oid);
			/*
			 * Regardless of what the file header said,
			 * we definitely know the value of *this*
			 * reference:
			 */
			last->flag |= REF_KNOWS_PEELED;
		}
	}

	fclose(f);
	strbuf_release(&line);

	return packed_refs;
}