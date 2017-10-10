	ctx.fmt = rev.commit_format;

	strbuf_addstr(&out, "Squashed commit of the following:\n");
	while ((commit = get_revision(&rev)) != NULL) {
		strbuf_addch(&out, '\n');
		strbuf_addf(&out, "commit %s\n",
			sha1_to_hex(commit->object.sha1));
		pretty_print_commit(&ctx, commit, &out);
	}
	if (write_in_full(fd, out.buf, out.len) != out.len)
		die_errno(_("Writing SQUASH_MSG"));
	if (close(fd))
		die_errno(_("Finishing SQUASH_MSG"));
