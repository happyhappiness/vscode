static int write_rr(struct string_list *rr, int out_fd)
{
	int i;
	for (i = 0; i < rr->nr; i++) {
		struct strbuf buf = STRBUF_INIT;
		struct rerere_id *id;

		assert(rr->items[i].util != RERERE_RESOLVED);

		id = rr->items[i].util;
		if (!id)
			continue;
		assert(id->variant >= 0);
		if (0 < id->variant)
			strbuf_addf(&buf, "%s.%d\t%s%c",
				    rerere_id_hex(id), id->variant,
				    rr->items[i].string, 0);
		else
			strbuf_addf(&buf, "%s\t%s%c",
				    rerere_id_hex(id),
				    rr->items[i].string, 0);

		if (write_in_full(out_fd, buf.buf, buf.len) != buf.len)
			die("unable to write rerere record");

		strbuf_release(&buf);
	}
	if (commit_lock_file(&write_lock) != 0)
		die("unable to write rerere record");
	return 0;
}