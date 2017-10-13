tatic void update_remote_refs(const struct ref *refs,
			       const struct ref *mapped_refs,
			       const struct ref *remote_head_points_at,
			       const char *branch_top,
			       const char *msg,
			       struct transport *transport,
			       int check_connectivity)
{
	const struct ref *rm = mapped_refs;

	if (check_connectivity) {
		if (transport->progress)
			fprintf(stderr, _("Checking connectivity... "));
		if (check_everything_connected_with_transport(iterate_ref_map,
							      0, &rm, transport))
			die(_("remote did not send all necessary objects"));
		if (transport->progress)
			fprintf(stderr, _("done.\n"));
	}

	if (refs) {
		write_remote_refs(mapped_refs);
		if (option_single_branch)
			write_followtags(refs, msg);
	}

	if (remote_head_points_at && !option_bare) {
		struct strbuf head_ref = STRBUF_INIT;
		strbuf_addstr(&head_ref, branch_top);
		strbuf_addstr(&head_ref, "HEAD");
		if (create_symref(head_ref.buf,
				  remote_head_points_at->peer_ref->name,
				  msg) < 0)
			die(_("unable to update %s"), head_ref.buf);
		strbuf_release(&head_ref);
	}
}