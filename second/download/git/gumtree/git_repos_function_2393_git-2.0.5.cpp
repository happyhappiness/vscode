static void read_packed_refs(FILE *f, struct ref_dir *dir)
{
	struct ref_entry *last = NULL;
	char refline[PATH_MAX];
	enum { PEELED_NONE, PEELED_TAGS, PEELED_FULLY } peeled = PEELED_NONE;

	while (fgets(refline, sizeof(refline), f)) {
		unsigned char sha1[20];
		const char *refname;
		static const char header[] = "# pack-refs with:";

		if (!strncmp(refline, header, sizeof(header)-1)) {
			const char *traits = refline + sizeof(header) - 1;
			if (strstr(traits, " fully-peeled "))
				peeled = PEELED_FULLY;
			else if (strstr(traits, " peeled "))
				peeled = PEELED_TAGS;
			/* perhaps other traits later as well */
			continue;
		}

		refname = parse_ref_line(refline, sha1);
		if (refname) {
			last = create_ref_entry(refname, sha1, REF_ISPACKED, 1);
			if (peeled == PEELED_FULLY ||
			    (peeled == PEELED_TAGS && starts_with(refname, "refs/tags/")))
				last->flag |= REF_KNOWS_PEELED;
			add_ref(dir, last);
			continue;
		}
		if (last &&
		    refline[0] == '^' &&
		    strlen(refline) == PEELED_LINE_LENGTH &&
		    refline[PEELED_LINE_LENGTH - 1] == '\n' &&
		    !get_sha1_hex(refline + 1, sha1)) {
			hashcpy(last->u.value.peeled, sha1);
			/*
			 * Regardless of what the file header said,
			 * we definitely know the value of *this*
			 * reference:
			 */
			last->flag |= REF_KNOWS_PEELED;
		}
	}
}