			type = ' ';
			msg = NULL;
		}
		strbuf_add_unique_abbrev(&quickref, ref->new_oid.hash,
					 DEFAULT_ABBREV);

		print_ref_status(type, quickref.buf, ref, ref->peer_ref, msg,
				 porcelain, summary_width);
		strbuf_release(&quickref);
	}
}

static int print_one_push_status(struct ref *ref, const char *dest, int count,
				 int porcelain, int summary_width)
{
	if (!count) {
		char *url = transport_anonymize_url(dest);
		fprintf(porcelain ? stdout : stderr, "To %s\n", url);
		free(url);
	}

	switch(ref->status) {
	case REF_STATUS_NONE:
		print_ref_status('X', "[no match]", ref, NULL, NULL,
				 porcelain, summary_width);
		break;
	case REF_STATUS_REJECT_NODELETE:
		print_ref_status('!', "[rejected]", ref, NULL,
				 "remote does not support deleting refs",
				 porcelain, summary_width);
		break;
	case REF_STATUS_UPTODATE:
		print_ref_status('=', "[up to date]", ref,
				 ref->peer_ref, NULL, porcelain, summary_width);
		break;
	case REF_STATUS_REJECT_NONFASTFORWARD:
		print_ref_status('!', "[rejected]", ref, ref->peer_ref,
				 "non-fast-forward", porcelain, summary_width);
		break;
	case REF_STATUS_REJECT_ALREADY_EXISTS:
		print_ref_status('!', "[rejected]", ref, ref->peer_ref,
				 "already exists", porcelain, summary_width);
		break;
	case REF_STATUS_REJECT_FETCH_FIRST:
		print_ref_status('!', "[rejected]", ref, ref->peer_ref,
				 "fetch first", porcelain, summary_width);
		break;
	case REF_STATUS_REJECT_NEEDS_FORCE:
		print_ref_status('!', "[rejected]", ref, ref->peer_ref,
				 "needs force", porcelain, summary_width);
		break;
	case REF_STATUS_REJECT_STALE:
		print_ref_status('!', "[rejected]", ref, ref->peer_ref,
				 "stale info", porcelain, summary_width);
		break;
	case REF_STATUS_REJECT_SHALLOW:
		print_ref_status('!', "[rejected]", ref, ref->peer_ref,
				 "new shallow roots not allowed",
				 porcelain, summary_width);
		break;
	case REF_STATUS_REMOTE_REJECT:
		print_ref_status('!', "[remote rejected]", ref,
				 ref->deletion ? NULL : ref->peer_ref,
				 ref->remote_status, porcelain, summary_width);
		break;
	case REF_STATUS_EXPECTING_REPORT:
		print_ref_status('!', "[remote failure]", ref,
				 ref->deletion ? NULL : ref->peer_ref,
				 "remote failed to report status",
				 porcelain, summary_width);
		break;
	case REF_STATUS_ATOMIC_PUSH_FAILED:
		print_ref_status('!', "[rejected]", ref, ref->peer_ref,
				 "atomic push failed", porcelain, summary_width);
		break;
	case REF_STATUS_OK:
		print_ok_ref_status(ref, porcelain, summary_width);
		break;
	}

	return 1;
}

static int measure_abbrev(const struct object_id *oid, int sofar)
{
	char hex[GIT_SHA1_HEXSZ + 1];
	int w = find_unique_abbrev_r(hex, oid->hash, DEFAULT_ABBREV);

	return (w < sofar) ? sofar : w;
}

int transport_summary_width(const struct ref *refs)
{
	int maxw = -1;

	for (; refs; refs = refs->next) {
		maxw = measure_abbrev(&refs->old_oid, maxw);
		maxw = measure_abbrev(&refs->new_oid, maxw);
	}
	if (maxw < 0)
		maxw = FALLBACK_DEFAULT_ABBREV;
	return (2 * maxw + 3);
}

void transport_print_push_status(const char *dest, struct ref *refs,
				  int verbose, int porcelain, unsigned int *reject_reasons)
{
	struct ref *ref;
	int n = 0;
	unsigned char head_sha1[20];
	char *head;
	int summary_width = transport_summary_width(refs);

	head = resolve_refdup("HEAD", RESOLVE_REF_READING, head_sha1, NULL);

	if (verbose) {
		for (ref = refs; ref; ref = ref->next)
			if (ref->status == REF_STATUS_UPTODATE)
				n += print_one_push_status(ref, dest, n,
							   porcelain, summary_width);
	}

	for (ref = refs; ref; ref = ref->next)
		if (ref->status == REF_STATUS_OK)
			n += print_one_push_status(ref, dest, n,
						   porcelain, summary_width);

	*reject_reasons = 0;
	for (ref = refs; ref; ref = ref->next) {
		if (ref->status != REF_STATUS_NONE &&
		    ref->status != REF_STATUS_UPTODATE &&
		    ref->status != REF_STATUS_OK)
			n += print_one_push_status(ref, dest, n,
						   porcelain, summary_width);
		if (ref->status == REF_STATUS_REJECT_NONFASTFORWARD) {
			if (head != NULL && !strcmp(head, ref->name))
				*reject_reasons |= REJECT_NON_FF_HEAD;
			else
				*reject_reasons |= REJECT_NON_FF_OTHER;
		} else if (ref->status == REF_STATUS_REJECT_ALREADY_EXISTS) {
