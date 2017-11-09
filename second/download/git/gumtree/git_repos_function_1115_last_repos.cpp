static void abbrev_sha1_in_line(struct strbuf *line)
{
	struct strbuf **split;
	int i;

	if (starts_with(line->buf, "exec ") ||
	    starts_with(line->buf, "x "))
		return;

	split = strbuf_split_max(line, ' ', 3);
	if (split[0] && split[1]) {
		struct object_id oid;

		/*
		 * strbuf_split_max left a space. Trim it and re-add
		 * it after abbreviation.
		 */
		strbuf_trim(split[1]);
		if (!get_oid(split[1]->buf, &oid)) {
			strbuf_reset(split[1]);
			strbuf_add_unique_abbrev(split[1], oid.hash,
						 DEFAULT_ABBREV);
			strbuf_addch(split[1], ' ');
			strbuf_reset(line);
			for (i = 0; split[i]; i++)
				strbuf_addbuf(line, split[i]);
		}
	}
	strbuf_list_free(split);
}