
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
