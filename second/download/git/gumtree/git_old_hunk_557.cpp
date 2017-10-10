			type = ' ';
			msg = NULL;
		}
		strbuf_add_unique_abbrev(&quickref, ref->new_oid.hash,
					 DEFAULT_ABBREV);

		print_ref_status(type, quickref.buf, ref, ref->peer_ref, msg, porcelain);
		strbuf_release(&quickref);
	}
}

static int print_one_push_status(struct ref *ref, const char *dest, int count, int porcelain)
{
	if (!count) {
		char *url = transport_anonymize_url(dest);
		fprintf(porcelain ? stdout : stderr, "To %s\n", url);
		free(url);
	}

	switch(ref->status) {
	case REF_STATUS_NONE:
		print_ref_status('X', "[no match]", ref, NULL, NULL, porcelain);
		break;
	case REF_STATUS_REJECT_NODELETE:
		print_ref_status('!', "[rejected]", ref, NULL,
						 "remote does not support deleting refs", porcelain);
		break;
	case REF_STATUS_UPTODATE:
		print_ref_status('=', "[up to date]", ref,
						 ref->peer_ref, NULL, porcelain);
		break;
	case REF_STATUS_REJECT_NONFASTFORWARD:
		print_ref_status('!', "[rejected]", ref, ref->peer_ref,
						 "non-fast-forward", porcelain);
		break;
	case REF_STATUS_REJECT_ALREADY_EXISTS:
		print_ref_status('!', "[rejected]", ref, ref->peer_ref,
						 "already exists", porcelain);
		break;
	case REF_STATUS_REJECT_FETCH_FIRST:
		print_ref_status('!', "[rejected]", ref, ref->peer_ref,
						 "fetch first", porcelain);
		break;
	case REF_STATUS_REJECT_NEEDS_FORCE:
		print_ref_status('!', "[rejected]", ref, ref->peer_ref,
						 "needs force", porcelain);
		break;
	case REF_STATUS_REJECT_STALE:
		print_ref_status('!', "[rejected]", ref, ref->peer_ref,
						 "stale info", porcelain);
		break;
	case REF_STATUS_REJECT_SHALLOW:
		print_ref_status('!', "[rejected]", ref, ref->peer_ref,
						 "new shallow roots not allowed", porcelain);
		break;
	case REF_STATUS_REMOTE_REJECT:
		print_ref_status('!', "[remote rejected]", ref,
						 ref->deletion ? NULL : ref->peer_ref,
						 ref->remote_status, porcelain);
		break;
	case REF_STATUS_EXPECTING_REPORT:
		print_ref_status('!', "[remote failure]", ref,
						 ref->deletion ? NULL : ref->peer_ref,
						 "remote failed to report status", porcelain);
		break;
	case REF_STATUS_ATOMIC_PUSH_FAILED:
		print_ref_status('!', "[rejected]", ref, ref->peer_ref,
						 "atomic push failed", porcelain);
		break;
	case REF_STATUS_OK:
		print_ok_ref_status(ref, porcelain);
		break;
	}

	return 1;
}

void transport_print_push_status(const char *dest, struct ref *refs,
				  int verbose, int porcelain, unsigned int *reject_reasons)
{
	struct ref *ref;
	int n = 0;
	unsigned char head_sha1[20];
	char *head;

	head = resolve_refdup("HEAD", RESOLVE_REF_READING, head_sha1, NULL);

	if (verbose) {
		for (ref = refs; ref; ref = ref->next)
			if (ref->status == REF_STATUS_UPTODATE)
				n += print_one_push_status(ref, dest, n, porcelain);
	}

	for (ref = refs; ref; ref = ref->next)
		if (ref->status == REF_STATUS_OK)
			n += print_one_push_status(ref, dest, n, porcelain);

	*reject_reasons = 0;
	for (ref = refs; ref; ref = ref->next) {
		if (ref->status != REF_STATUS_NONE &&
		    ref->status != REF_STATUS_UPTODATE &&
		    ref->status != REF_STATUS_OK)
			n += print_one_push_status(ref, dest, n, porcelain);
		if (ref->status == REF_STATUS_REJECT_NONFASTFORWARD) {
			if (head != NULL && !strcmp(head, ref->name))
				*reject_reasons |= REJECT_NON_FF_HEAD;
			else
				*reject_reasons |= REJECT_NON_FF_OTHER;
		} else if (ref->status == REF_STATUS_REJECT_ALREADY_EXISTS) {
