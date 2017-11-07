static void print_ok_ref_status(struct ref *ref, int porcelain)
{
	if (ref->deletion)
		print_ref_status('-', "[deleted]", ref, NULL, NULL, porcelain);
	else if (is_null_oid(&ref->old_oid))
		print_ref_status('*',
			(starts_with(ref->name, "refs/tags/") ? "[new tag]" :
			"[new branch]"),
			ref, ref->peer_ref, NULL, porcelain);
	else {
		struct strbuf quickref = STRBUF_INIT;
		char type;
		const char *msg;

		strbuf_add_unique_abbrev(&quickref, ref->old_oid.hash,
					 DEFAULT_ABBREV);
		if (ref->forced_update) {
			strbuf_addstr(&quickref, "...");
			type = '+';
			msg = "forced update";
		} else {
			strbuf_addstr(&quickref, "..");
			type = ' ';
			msg = NULL;
		}
		strbuf_add_unique_abbrev(&quickref, ref->new_oid.hash,
					 DEFAULT_ABBREV);

		print_ref_status(type, quickref.buf, ref, ref->peer_ref, msg, porcelain);
		strbuf_release(&quickref);
	}
}