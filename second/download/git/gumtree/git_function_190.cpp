static void show_stats(struct apply_state *state, struct patch *patch)
{
	struct strbuf qname = STRBUF_INIT;
	char *cp = patch->new_name ? patch->new_name : patch->old_name;
	int max, add, del;

	quote_c_style(cp, &qname, NULL, 0);

	/*
	 * "scale" the filename
	 */
	max = state->max_len;
	if (max > 50)
		max = 50;

	if (qname.len > max) {
		cp = strchr(qname.buf + qname.len + 3 - max, '/');
		if (!cp)
			cp = qname.buf + qname.len + 3 - max;
		strbuf_splice(&qname, 0, cp - qname.buf, "...", 3);
	}

	if (patch->is_binary) {
		printf(" %-*s |  Bin\n", max, qname.buf);
		strbuf_release(&qname);
		return;
	}

	printf(" %-*s |", max, qname.buf);
	strbuf_release(&qname);

	/*
	 * scale the add/delete
	 */
	max = max + state->max_change > 70 ? 70 - max : state->max_change;
	add = patch->lines_added;
	del = patch->lines_deleted;

	if (state->max_change > 0) {
		int total = ((add + del) * max + state->max_change / 2) / state->max_change;
		add = (add * max + state->max_change / 2) / state->max_change;
		del = total - add;
	}
	printf("%5d %.*s%.*s\n", patch->lines_added + patch->lines_deleted,
		add, pluses, del, minuses);
}