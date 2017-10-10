}

static const char edit_description[] = "BRANCH_DESCRIPTION";

static int edit_branch_description(const char *branch_name)
{
	FILE *fp;
	int status;
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
	fp = fopen(git_path(edit_description), "w");
	if ((fwrite(buf.buf, 1, buf.len, fp) < buf.len) || fclose(fp)) {
		strbuf_release(&buf);
		return error(_("could not write branch description template: %s"),
			     strerror(errno));
	}
	strbuf_reset(&buf);
	if (launch_editor(git_path(edit_description), &buf, NULL)) {
