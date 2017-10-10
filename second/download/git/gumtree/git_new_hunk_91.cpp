		append_signoff(&sb, ignore_footer, 0);
	}

	if (fwrite(sb.buf, 1, sb.len, s->fp) < sb.len)
		die_errno(_("could not write commit template"));

	if (auto_comment_line_char)
		adjust_comment_line_char(&sb);
	strbuf_release(&sb);

	/* This checks if committer ident is explicitly given */
	strbuf_addstr(&committer_ident, git_committer_info(IDENT_STRICT));
	if (use_editor && include_status) {
		int ident_shown = 0;
		int saved_color_setting;
		struct ident_split ci, ai;

		if (whence != FROM_COMMIT) {
			if (cleanup_mode == CLEANUP_SCISSORS)
				wt_status_add_cut_line(s->fp);
			status_printf_ln(s, GIT_COLOR_NORMAL,
			    whence == FROM_MERGE
				? _("\n"
