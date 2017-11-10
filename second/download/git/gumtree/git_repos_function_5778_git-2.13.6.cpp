static void fmt_merge_msg_title(struct strbuf *out,
	const char *current_branch) {
	int i = 0;
	char *sep = "";

	strbuf_addstr(out, "Merge ");
	for (i = 0; i < srcs.nr; i++) {
		struct src_data *src_data = srcs.items[i].util;
		const char *subsep = "";

		strbuf_addstr(out, sep);
		sep = "; ";

		if (src_data->head_status == 1) {
			strbuf_addstr(out, srcs.items[i].string);
			continue;
		}
		if (src_data->head_status == 3) {
			subsep = ", ";
			strbuf_addstr(out, "HEAD");
		}
		if (src_data->branch.nr) {
			strbuf_addstr(out, subsep);
			subsep = ", ";
			print_joined("branch ", "branches ", &src_data->branch,
					out);
		}
		if (src_data->r_branch.nr) {
			strbuf_addstr(out, subsep);
			subsep = ", ";
			print_joined("remote-tracking branch ", "remote-tracking branches ",
					&src_data->r_branch, out);
		}
		if (src_data->tag.nr) {
			strbuf_addstr(out, subsep);
			subsep = ", ";
			print_joined("tag ", "tags ", &src_data->tag, out);
		}
		if (src_data->generic.nr) {
			strbuf_addstr(out, subsep);
			print_joined("commit ", "commits ", &src_data->generic,
					out);
		}
		if (strcmp(".", srcs.items[i].string))
			strbuf_addf(out, " of %s", srcs.items[i].string);
	}

	if (!strcmp("master", current_branch))
		strbuf_addch(out, '\n');
	else
		strbuf_addf(out, " into %s\n", current_branch);
}