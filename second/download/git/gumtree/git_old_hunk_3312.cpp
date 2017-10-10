			die(_("confusion beyond insanity"));
		REALLOC_ARRAY(objects, nr_objects + nr_unresolved + 1);
		memset(objects + nr_objects + 1, 0,
		       nr_unresolved * sizeof(*objects));
		f = sha1fd(output_fd, curr_pack);
		fix_unresolved_deltas(f);
		strbuf_addf(&msg, _("completed with %d local objects"),
			    nr_objects - nr_objects_initial);
		stop_progress_msg(&progress, msg.buf);
		strbuf_release(&msg);
		sha1close(f, tail_sha1, 0);
		hashcpy(read_sha1, pack_sha1);
		fixup_pack_header_footer(output_fd, pack_sha1,
