static void read_packed_refs(FILE *f, struct ref_dir *dir)
{
	struct ref_entry *last = NULL;
	struct strbuf line = STRBUF_INIT;
	enum { PEELED_NONE, PEELED_TAGS, PEELED_FULLY } peeled = PEELED_NONE;

	while (strbuf_getwholeline(&line, f, '\n') != EOF) {
		unsigned char sha1[20];
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

		refname = parse_ref_line(&line, sha1);
		if (refname) {
			int flag = REF_ISPACKED;

			if (check_refname_format(refname, REFNAME_ALLOW_ONELEVEL)) {
				hashclr(sha1);
				flag |= REF_BAD_NAME | REF_ISBROKEN;
			}
			last = create_ref_entry(refname, sha1, flag, 0);
			if (peeled == PEELED_FULLY ||
			    (peeled == PEELED_TAGS && starts_with(refname, "refs/tags/")))
				last->flag |= REF_KNOWS_PEELED;
			add_ref(dir, last);
			continue;
		}
		if (last &&
		    line.buf[0] == '^' &&
		    line.len == PEELED_LINE_LENGTH &&
		    line.buf[PEELED_LINE_LENGTH - 1] == '\n' &&
		    !get_sha1_hex(line.buf + 1, sha1)) {
			hashcpy(last->u.value.peeled, sha1);
			/*
			 * Regardless of what the file header said,
			 * we definitely know the value of *this*
			 * reference:
			 */
			last->flag |= REF_KNOWS_PEELED;
		}
	}

	strbuf_release(&line);
}