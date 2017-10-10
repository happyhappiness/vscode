	printf(" %-*s |", max, qname.buf);
	strbuf_release(&qname);

	/*
	 * scale the add/delete
	 */
	max = max + max_change > 70 ? 70 - max : max_change;
	add = patch->lines_added;
	del = patch->lines_deleted;

	if (max_change > 0) {
		int total = ((add + del) * max + max_change / 2) / max_change;
		add = (add * max + max_change / 2) / max_change;
		del = total - add;
	}
	printf("%5d %.*s%.*s\n", patch->lines_added + patch->lines_deleted,
		add, pluses, del, minuses);
}

