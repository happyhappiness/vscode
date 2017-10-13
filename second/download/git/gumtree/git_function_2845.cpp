static int edit_branch_description(const char *branch_name)
{
	struct strbuf buf = STRBUF_INIT;
	struct strbuf name = STRBUF_INIT;

	read_branch_desc(&buf, branch_name);
	if (!buf.len || buf.buf[buf.len-1] != '\n')
		strbuf_addch(&buf, '\n');
	strbuf_commented_addf(&buf,
		    "Please edit the description for the branch\n"
		    "  %s\n"
		    "Lines starting with '%c' will be stripped.\n",
		    branch_name, comment_line_char);
	if (write_file_gently(git_path(edit_description), "%s", buf.buf)) {
		strbuf_release(&buf);
		return error(_("could not write branch description template: %s"),
			     strerror(errno));
	}
	strbuf_reset(&buf);
	if (launch_editor(git_path(edit_description), &buf, NULL)) {
		strbuf_release(&buf);
		return -1;
	}
	strbuf_stripspace(&buf, 1);

	strbuf_addf(&name, "branch.%s.description", branch_name);
	git_config_set(name.buf, buf.len ? buf.buf : NULL);
	strbuf_release(&name);
	strbuf_release(&buf);

	return 0;
}