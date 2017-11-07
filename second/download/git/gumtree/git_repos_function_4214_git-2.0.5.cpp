static int get_one_patchid(unsigned char *next_sha1, git_SHA_CTX *ctx, struct strbuf *line_buf)
{
	int patchlen = 0, found_next = 0;
	int before = -1, after = -1;

	while (strbuf_getwholeline(line_buf, stdin, '\n') != EOF) {
		char *line = line_buf->buf;
		char *p = line;
		int len;

		if (!memcmp(line, "diff-tree ", 10))
			p += 10;
		else if (!memcmp(line, "commit ", 7))
			p += 7;
		else if (!memcmp(line, "From ", 5))
			p += 5;
		else if (!memcmp(line, "\\ ", 2) && 12 < strlen(line))
			continue;

		if (!get_sha1_hex(p, next_sha1)) {
			found_next = 1;
			break;
		}

		/* Ignore commit comments */
		if (!patchlen && memcmp(line, "diff ", 5))
			continue;

		/* Parsing diff header?  */
		if (before == -1) {
			if (!memcmp(line, "index ", 6))
				continue;
			else if (!memcmp(line, "--- ", 4))
				before = after = 1;
			else if (!isalpha(line[0]))
				break;
		}

		/* Looking for a valid hunk header?  */
		if (before == 0 && after == 0) {
			if (!memcmp(line, "@@ -", 4)) {
				/* Parse next hunk, but ignore line numbers.  */
				scan_hunk_header(line, &before, &after);
				continue;
			}

			/* Split at the end of the patch.  */
			if (memcmp(line, "diff ", 5))
				break;

			/* Else we're parsing another header.  */
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
		git_SHA1_Update(ctx, line, len);
	}

	if (!found_next)
		hashclr(next_sha1);

	return patchlen;
}