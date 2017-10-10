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

static void update_head(const struct ref *our, const struct ref *remote,
			const char *msg)
{
	const char *head;
	if (our && skip_prefix(our->name, "refs/heads/", &head)) {
		/* Local default branch link */
		if (create_symref("HEAD", our->name, NULL) < 0)
			die(_("unable to update HEAD"));
		if (!option_bare) {
			update_ref(msg, "HEAD", our->old_oid.hash, NULL, 0,
				   UPDATE_REFS_DIE_ON_ERR);
			install_branch_config(0, head, option_origin, our->name);
		}
	} else if (our) {
