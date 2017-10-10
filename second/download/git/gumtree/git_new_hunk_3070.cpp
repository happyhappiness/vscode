	if (git_config_rename_section(buf.buf, buf2.buf) < 1)
		return error(_("Could not rename config section '%s' to '%s'"),
				buf.buf, buf2.buf);

	strbuf_reset(&buf);
	strbuf_addf(&buf, "remote.%s.fetch", rename.new);
	git_config_set_multivar(buf.buf, NULL, NULL, 1);
	strbuf_addf(&old_remote_context, ":refs/remotes/%s/", rename.old);
	for (i = 0; i < oldremote->fetch_refspec_nr; i++) {
		char *ptr;

		strbuf_reset(&buf2);
		strbuf_addstr(&buf2, oldremote->fetch_refspec[i]);
