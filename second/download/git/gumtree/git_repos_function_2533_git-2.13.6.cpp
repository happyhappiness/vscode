void transport_print_push_status(const char *dest, struct ref *refs,
				  int verbose, int porcelain, unsigned int *reject_reasons)
{
	struct ref *ref;
	int n = 0;
	struct object_id head_oid;
	char *head;
	int summary_width = transport_summary_width(refs);

	head = resolve_refdup("HEAD", RESOLVE_REF_READING, head_oid.hash, NULL);

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
			*reject_reasons |= REJECT_ALREADY_EXISTS;
		} else if (ref->status == REF_STATUS_REJECT_FETCH_FIRST) {
			*reject_reasons |= REJECT_FETCH_FIRST;
		} else if (ref->status == REF_STATUS_REJECT_NEEDS_FORCE) {
			*reject_reasons |= REJECT_NEEDS_FORCE;
		}
	}
	free(head);
}