	if (!c)
		return 0;

	fp = xfopen(am_path(state, "rewritten"), "r");

	while (!strbuf_getline_lf(&sb, fp)) {
		struct object_id from_obj, to_obj;

		if (sb.len != GIT_SHA1_HEXSZ * 2 + 1) {
			ret = error(invalid_line, sb.buf);
			goto finish;
		}

		if (get_oid_hex(sb.buf, &from_obj)) {
			ret = error(invalid_line, sb.buf);
			goto finish;
		}

		if (sb.buf[GIT_SHA1_HEXSZ] != ' ') {
			ret = error(invalid_line, sb.buf);
			goto finish;
		}

		if (get_oid_hex(sb.buf + GIT_SHA1_HEXSZ + 1, &to_obj)) {
			ret = error(invalid_line, sb.buf);
			goto finish;
		}

		if (copy_note_for_rewrite(c, from_obj.hash, to_obj.hash))
			ret = error(_("Failed to copy notes from '%s' to '%s'"),
					oid_to_hex(&from_obj), oid_to_hex(&to_obj));
	}

finish:
	finish_copy_notes_for_rewrite(c, msg);
	fclose(fp);
	strbuf_release(&sb);
