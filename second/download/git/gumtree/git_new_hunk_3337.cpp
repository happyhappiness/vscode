		    "Please edit the description for the branch\n"
		    "  %s\n"
		    "Lines starting with '%c' will be stripped.\n",
		    branch_name, comment_line_char);
	if (write_file_gently(git_path(edit_description), "%s", buf.buf)) {
		strbuf_release(&buf);
		return error_errno(_("could not write branch description template"));
	}
	strbuf_reset(&buf);
	if (launch_editor(git_path(edit_description), &buf, NULL)) {
		strbuf_release(&buf);
		return -1;
	}
