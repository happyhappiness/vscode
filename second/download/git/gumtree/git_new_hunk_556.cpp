			fputc(')', stderr);
		}
		fputc('\n', stderr);
	}
}

static void print_ok_ref_status(struct ref *ref, int porcelain, int summary_width)
{
	if (ref->deletion)
		print_ref_status('-', "[deleted]", ref, NULL, NULL,
				 porcelain, summary_width);
	else if (is_null_oid(&ref->old_oid))
		print_ref_status('*',
			(starts_with(ref->name, "refs/tags/") ? "[new tag]" :
			"[new branch]"),
			ref, ref->peer_ref, NULL, porcelain, summary_width);
	else {
		struct strbuf quickref = STRBUF_INIT;
		char type;
		const char *msg;

		strbuf_add_unique_abbrev(&quickref, ref->old_oid.hash,
