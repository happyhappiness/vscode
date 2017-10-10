		if (!commit)
			die(_("could not lookup commit %s"), fixup_message);
		ctx.output_encoding = get_commit_output_encoding();
		format_commit_message(commit, "fixup! %s\n\n",
				      &sb, &ctx);
		hook_arg1 = "message";
	} else if (!stat(git_path_merge_msg(), &statbuf)) {
		if (strbuf_read_file(&sb, git_path_merge_msg(), 0) < 0)
			die_errno(_("could not read MERGE_MSG"));
		hook_arg1 = "merge";
	} else if (!stat(git_path_squash_msg(), &statbuf)) {
		if (strbuf_read_file(&sb, git_path_squash_msg(), 0) < 0)
			die_errno(_("could not read SQUASH_MSG"));
		hook_arg1 = "squash";
	} else if (template_file) {
		if (strbuf_read_file(&sb, template_file, 0) < 0)
			die_errno(_("could not read '%s'"), template_file);
		hook_arg1 = "template";
