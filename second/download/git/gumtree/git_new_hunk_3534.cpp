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
