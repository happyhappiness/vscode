	if (shallow_update && !checked_connectivity)
		error("BUG: run 'git fsck' for safety.\n"
		      "If there are errors, try to remove "
		      "the reported refs above");
}

static struct command **queue_command(struct command **tail,
				      const char *line,
				      int linelen)
{
	unsigned char old_sha1[20], new_sha1[20];
	struct command *cmd;
	const char *refname;
	int reflen;

	if (linelen < 83 ||
	    line[40] != ' ' ||
	    line[81] != ' ' ||
	    get_sha1_hex(line, old_sha1) ||
	    get_sha1_hex(line + 41, new_sha1))
		die("protocol error: expected old/new/ref, got '%s'", line);

	refname = line + 82;
	reflen = linelen - 82;
	cmd = xcalloc(1, sizeof(struct command) + reflen + 1);
	hashcpy(cmd->old_sha1, old_sha1);
	hashcpy(cmd->new_sha1, new_sha1);
	memcpy(cmd->ref_name, refname, reflen);
	cmd->ref_name[reflen] = '\0';
	*tail = cmd;
	return &cmd->next;
}

static void queue_commands_from_cert(struct command **tail,
				     struct strbuf *push_cert)
{
	const char *boc, *eoc;

	if (*tail)
		die("protocol error: got both push certificate and unsigned commands");

	boc = strstr(push_cert->buf, "\n\n");
	if (!boc)
		die("malformed push certificate %.*s", 100, push_cert->buf);
	else
		boc += 2;
	eoc = push_cert->buf + parse_signature(push_cert->buf, push_cert->len);

	while (boc < eoc) {
		const char *eol = memchr(boc, '\n', eoc - boc);
		tail = queue_command(tail, boc, eol ? eol - boc : eoc - eol);
		boc = eol ? eol + 1 : eoc;
	}
}

static struct command *read_head_info(struct sha1_array *shallow)
{
	struct command *commands = NULL;
	struct command **p = &commands;
	for (;;) {
		char *line;
		int len, linelen;

		line = packet_read_line(0, &len);
		if (!line)
			break;

		if (len == 48 && starts_with(line, "shallow ")) {
			unsigned char sha1[20];
			if (get_sha1_hex(line + 8, sha1))
				die("protocol error: expected shallow sha, got '%s'",
				    line + 8);
			sha1_array_append(shallow, sha1);
			continue;
		}

		linelen = strlen(line);
		if (linelen < len) {
			const char *feature_list = line + linelen + 1;
			if (parse_feature_request(feature_list, "report-status"))
				report_status = 1;
			if (parse_feature_request(feature_list, "side-band-64k"))
				use_sideband = LARGE_PACKET_MAX;
			if (parse_feature_request(feature_list, "quiet"))
				quiet = 1;
		}

		if (!strcmp(line, "push-cert")) {
			int true_flush = 0;
			char certbuf[1024];

			for (;;) {
				len = packet_read(0, NULL, NULL,
						  certbuf, sizeof(certbuf), 0);
				if (!len) {
					true_flush = 1;
					break;
				}
				if (!strcmp(certbuf, "push-cert-end\n"))
					break; /* end of cert */
				strbuf_addstr(&push_cert, certbuf);
			}

			if (true_flush)
				break;
			continue;
		}

		p = queue_command(p, line, linelen);
	}

	if (push_cert.len)
		queue_commands_from_cert(p, &push_cert);

	return commands;
}

static const char *parse_pack_header(struct pack_header *hdr)
{
	switch (read_pack_header(0, hdr)) {
