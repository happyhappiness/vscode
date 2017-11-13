static void conclude_pack(int fix_thin_pack, const char *curr_pack, unsigned char *pack_sha1)
{
	if (nr_deltas == nr_resolved_deltas) {
		stop_progress(&progress);
		/* Flush remaining pack final 20-byte SHA1. */
		flush();
		return;
	}

	if (fix_thin_pack) {
		struct sha1file *f;
		unsigned char read_sha1[20], tail_sha1[20];
		struct strbuf msg = STRBUF_INIT;
		int nr_unresolved = nr_deltas - nr_resolved_deltas;
		int nr_objects_initial = nr_objects;
		if (nr_unresolved <= 0)
			die(_("confusion beyond insanity"));
		REALLOC_ARRAY(objects, nr_objects + nr_unresolved + 1);
		memset(objects + nr_objects + 1, 0,
		       nr_unresolved * sizeof(*objects));
		f = sha1fd(output_fd, curr_pack);
		fix_unresolved_deltas(f, nr_unresolved);
		strbuf_addf(&msg, _("completed with %d local objects"),
			    nr_objects - nr_objects_initial);
		stop_progress_msg(&progress, msg.buf);
		strbuf_release(&msg);
		sha1close(f, tail_sha1, 0);
		hashcpy(read_sha1, pack_sha1);
		fixup_pack_header_footer(output_fd, pack_sha1,
					 curr_pack, nr_objects,
					 read_sha1, consumed_bytes-20);
		if (hashcmp(read_sha1, tail_sha1) != 0)
			die(_("Unexpected tail checksum for %s "
			      "(disk corruption?)"), curr_pack);
	}
	if (nr_deltas != nr_resolved_deltas)
		die(Q_("pack has %d unresolved delta",
		       "pack has %d unresolved deltas",
		       nr_deltas - nr_resolved_deltas),
		    nr_deltas - nr_resolved_deltas);
}