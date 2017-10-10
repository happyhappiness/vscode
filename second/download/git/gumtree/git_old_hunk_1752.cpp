	if (shallow_update && !checked_connectivity)
		error("BUG: run 'git fsck' for safety.\n"
		      "If there are errors, try to remove "
		      "the reported refs above");
}

static struct command *read_head_info(struct sha1_array *shallow)
{
	struct command *commands = NULL;
	struct command **p = &commands;
	for (;;) {
		char *line;
		unsigned char old_sha1[20], new_sha1[20];
		struct command *cmd;
		char *refname;
		int len, reflen;

		line = packet_read_line(0, &len);
		if (!line)
			break;

		if (len == 48 && starts_with(line, "shallow ")) {
			if (get_sha1_hex(line + 8, old_sha1))
				die("protocol error: expected shallow sha, got '%s'", line + 8);
			sha1_array_append(shallow, old_sha1);
			continue;
		}

		if (len < 83 ||
		    line[40] != ' ' ||
		    line[81] != ' ' ||
		    get_sha1_hex(line, old_sha1) ||
		    get_sha1_hex(line + 41, new_sha1))
			die("protocol error: expected old/new/ref, got '%s'",
			    line);

		refname = line + 82;
		reflen = strlen(refname);
		if (reflen + 82 < len) {
			const char *feature_list = refname + reflen + 1;
			if (parse_feature_request(feature_list, "report-status"))
				report_status = 1;
			if (parse_feature_request(feature_list, "side-band-64k"))
				use_sideband = LARGE_PACKET_MAX;
			if (parse_feature_request(feature_list, "quiet"))
				quiet = 1;
		}
		cmd = xcalloc(1, sizeof(struct command) + len - 80);
		hashcpy(cmd->old_sha1, old_sha1);
		hashcpy(cmd->new_sha1, new_sha1);
		memcpy(cmd->ref_name, line + 82, len - 81);
		*p = cmd;
		p = &cmd->next;
	}
	return commands;
}

static const char *parse_pack_header(struct pack_header *hdr)
{
	switch (read_pack_header(0, hdr)) {
