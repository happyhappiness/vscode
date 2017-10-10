		if (check_connected(iterate_ref_map, &rm, &opt))
			die(_("remote did not send all necessary objects"));
	}

	if (refs) {
		write_remote_refs(mapped_refs);
		if (option_single_branch)
			write_followtags(refs, msg);
	}

	if (remote_head_points_at && !option_bare) {
		struct strbuf head_ref = STRBUF_INIT;
		strbuf_addstr(&head_ref, branch_top);
