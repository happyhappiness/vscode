	if (!c)
		return 0;

	fp = xfopen(am_path(state, "rewritten"), "r");

	while (!strbuf_getline_lf(&sb, fp)) {
		unsigned char from_obj[GIT_SHA1_RAWSZ], to_obj[GIT_SHA1_RAWSZ];

		if (sb.len != GIT_SHA1_HEXSZ * 2 + 1) {
			ret = error(invalid_line, sb.buf);
			goto finish;
		}

		if (get_sha1_hex(sb.buf, from_obj)) {
			ret = error(invalid_line, sb.buf);
			goto finish;
		}

		if (sb.buf[GIT_SHA1_HEXSZ] != ' ') {
			ret = error(invalid_line, sb.buf);
			goto finish;
		}

		if (get_sha1_hex(sb.buf + GIT_SHA1_HEXSZ + 1, to_obj)) {
			ret = error(invalid_line, sb.buf);
			goto finish;
		}

		if (copy_note_for_rewrite(c, from_obj, to_obj))
			ret = error(_("Failed to copy notes from '%s' to '%s'"),
					sha1_to_hex(from_obj), sha1_to_hex(to_obj));
	}

finish:
	finish_copy_notes_for_rewrite(c, msg);
	fclose(fp);
	strbuf_release(&sb);
