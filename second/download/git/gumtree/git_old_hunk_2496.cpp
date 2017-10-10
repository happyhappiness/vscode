		strbuf_addch(&buf, '\n');
	strbuf_commented_addf(&buf,
		    "Please edit the description for the branch\n"
		    "  %s\n"
		    "Lines starting with '%c' will be stripped.\n",
		    branch_name, comment_line_char);
	if (write_file(git_path(edit_description), 0, "%s", buf.buf)) {
		strbuf_release(&buf);
		return error(_("could not write branch description template: %s"),
			     strerror(errno));
	}
	strbuf_reset(&buf);
	if (launch_editor(git_path(edit_description), &buf, NULL)) {
