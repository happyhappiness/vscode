
	ref_lock = lock_any_ref_for_update("HEAD",
					   !current_head
					   ? NULL
					   : current_head->object.sha1,
					   0, NULL);

	nl = strchr(sb.buf, '\n');
	if (nl)
		strbuf_setlen(&sb, nl + 1 - sb.buf);
	else
		strbuf_addch(&sb, '\n');
	strbuf_insert(&sb, 0, reflog_msg, strlen(reflog_msg));
	strbuf_insert(&sb, strlen(reflog_msg), ": ", 2);

	if (!ref_lock) {
		rollback_index_files();
		die(_("cannot lock HEAD ref"));
	}
	if (write_ref_sha1(ref_lock, sha1, sb.buf) < 0) {
		rollback_index_files();
		die(_("cannot update HEAD ref"));
	}

	unlink(git_path("CHERRY_PICK_HEAD"));
