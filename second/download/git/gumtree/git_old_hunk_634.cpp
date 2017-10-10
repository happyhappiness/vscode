		goto fail;
	}
	if (is_null_sha1(sha1)) {
		error(_("cannot abort from a branch yet to be born"));
		goto fail;
	}
	if (reset_for_rollback(sha1))
		goto fail;
	strbuf_release(&buf);
	return sequencer_remove_state(opts);
fail:
	strbuf_release(&buf);
