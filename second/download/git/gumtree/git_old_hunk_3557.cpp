			ref, ref->peer_ref, NULL, porcelain);
	else {
		struct strbuf quickref = STRBUF_INIT;
		char type;
		const char *msg;

		strbuf_addstr(&quickref, status_abbrev(ref->old_oid.hash));
		if (ref->forced_update) {
			strbuf_addstr(&quickref, "...");
			type = '+';
			msg = "forced update";
		} else {
			strbuf_addstr(&quickref, "..");
			type = ' ';
			msg = NULL;
		}
		strbuf_addstr(&quickref, status_abbrev(ref->new_oid.hash));

		print_ref_status(type, quickref.buf, ref, ref->peer_ref, msg, porcelain);
		strbuf_release(&quickref);
	}
}

