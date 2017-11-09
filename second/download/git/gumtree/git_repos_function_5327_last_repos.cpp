static int get_one_patchid(struct object_id *next_oid, struct object_id *result,
			   struct strbuf *line_buf, int stable)
{
	int patchlen = 0, found_next = 0;
	int before = -1, after = -1;
	git_SHA_CTX ctx;

	git_SHA1_Init(&ctx);
	oidclr(result);

	while (strbuf_getwholeline(line_buf, stdin, '\n') != EOF) {
		char *line = line_buf->buf;
		const char *p = line;
		int len;

		if (!skip_prefix(line, "diff-tree ", &p) &&
		    !skip_prefix(line, "commit ", &p) &&
		    !skip_prefix(line, "From ", &p) &&
		    starts_with(line, "\\ ") && 12 < strlen(line))
			continue;

		if (!get_oid_hex(p, next_oid)) {
			found_next = 1;
			break;
		}

		/* Ignore commit comments */
		if (!patchlen && !starts_with(line, "diff "))
			continue;

		/* Parsing diff header?  */
		if (before == -1) {
			if (starts_with(line, "index "))
				continue;
			else if (starts_with(line, "--- "))
				before = after = 1;
			else if (!isalpha(line[0]))
				break;
		}

		/* Looking for a valid hunk header?  */
		if (before == 0 && after == 0) {
			if (starts_with(line, "@@ -")) {
				/* Parse next hunk, but ignore line numbers.  */
				scan_hunk_header(line, &before, &after);
				continue;
			}

			/* Split at the end of the patch.  */
			if (!starts_with(line, "diff "))
				break;

			/* Else we're parsing another header.  */
			if (stable)
				flush_one_hunk(result, &ctx);
			before = after = -1;
		}

		/* If we get here, we're inside a hunk.  */
		if (line[0] == '-' || line[0] == ' ')
			before--;
		if (line[0] == '+' || line[0] == ' ')
			after--;

		/* Compute the sha without whitespace */
		len = remove_space(line);
		patchlen += len;
		git_SHA1_Update(&ctx, line, len);
	}

	if (!found_next)
		oidclr(next_oid);

	flush_one_hunk(result, &ctx);

	return patchlen;
}