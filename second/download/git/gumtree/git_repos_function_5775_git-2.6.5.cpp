void svndump_read(const char *url, const char *local_ref, const char *notes_ref)
{
	char *val;
	char *t;
	uint32_t active_ctx = DUMP_CTX;
	uint32_t len;

	reset_dump_ctx(url);
	while ((t = buffer_read_line(&input))) {
		val = strchr(t, ':');
		if (!val)
			continue;
		val++;
		if (*val != ' ')
			continue;
		val++;

		/* strlen(key) + 1 */
		switch (val - t - 1) {
		case sizeof("SVN-fs-dump-format-version"):
			if (constcmp(t, "SVN-fs-dump-format-version"))
				continue;
			dump_ctx.version = atoi(val);
			if (dump_ctx.version > 3)
				die("expected svn dump format version <= 3, found %"PRIu32,
				    dump_ctx.version);
			break;
		case sizeof("UUID"):
			if (constcmp(t, "UUID"))
				continue;
			strbuf_reset(&dump_ctx.uuid);
			strbuf_addstr(&dump_ctx.uuid, val);
			break;
		case sizeof("Revision-number"):
			if (constcmp(t, "Revision-number"))
				continue;
			if (active_ctx == NODE_CTX)
				handle_node();
			if (active_ctx == REV_CTX)
				begin_revision(local_ref);
			if (active_ctx != DUMP_CTX)
				end_revision(notes_ref);
			active_ctx = REV_CTX;
			reset_rev_ctx(atoi(val));
			strbuf_addf(&rev_ctx.note, "%s\n", t);
			break;
		case sizeof("Node-path"):
			if (constcmp(t, "Node-"))
				continue;
			if (!constcmp(t + strlen("Node-"), "path")) {
				if (active_ctx == NODE_CTX)
					handle_node();
				if (active_ctx == REV_CTX)
					begin_revision(local_ref);
				active_ctx = NODE_CTX;
				reset_node_ctx(val);
				strbuf_addf(&rev_ctx.note, "%s\n", t);
				break;
			}
			if (constcmp(t + strlen("Node-"), "kind"))
				continue;
			strbuf_addf(&rev_ctx.note, "%s\n", t);
			if (!strcmp(val, "dir"))
				node_ctx.type = REPO_MODE_DIR;
			else if (!strcmp(val, "file"))
				node_ctx.type = REPO_MODE_BLB;
			else
				fprintf(stderr, "Unknown node-kind: %s\n", val);
			break;
		case sizeof("Node-action"):
			if (constcmp(t, "Node-action"))
				continue;
			strbuf_addf(&rev_ctx.note, "%s\n", t);
			if (!strcmp(val, "delete")) {
				node_ctx.action = NODEACT_DELETE;
			} else if (!strcmp(val, "add")) {
				node_ctx.action = NODEACT_ADD;
			} else if (!strcmp(val, "change")) {
				node_ctx.action = NODEACT_CHANGE;
			} else if (!strcmp(val, "replace")) {
				node_ctx.action = NODEACT_REPLACE;
			} else {
				fprintf(stderr, "Unknown node-action: %s\n", val);
				node_ctx.action = NODEACT_UNKNOWN;
			}
			break;
		case sizeof("Node-copyfrom-path"):
			if (constcmp(t, "Node-copyfrom-path"))
				continue;
			strbuf_reset(&node_ctx.src);
			strbuf_addstr(&node_ctx.src, val);
			strbuf_addf(&rev_ctx.note, "%s\n", t);
			break;
		case sizeof("Node-copyfrom-rev"):
			if (constcmp(t, "Node-copyfrom-rev"))
				continue;
			node_ctx.srcRev = atoi(val);
			strbuf_addf(&rev_ctx.note, "%s\n", t);
			break;
		case sizeof("Text-content-length"):
			if (constcmp(t, "Text") && constcmp(t, "Prop"))
				continue;
			if (constcmp(t + 4, "-content-length"))
				continue;
			{
				char *end;
				uintmax_t len;

				len = strtoumax(val, &end, 10);
				if (!isdigit(*val) || *end)
					die("invalid dump: non-numeric length %s", val);
				if (len > maximum_signed_value_of_type(off_t))
					die("unrepresentable length in dump: %s", val);

				if (*t == 'T')
					node_ctx.text_length = (off_t) len;
				else
					node_ctx.prop_length = (off_t) len;
				break;
			}
		case sizeof("Text-delta"):
			if (!constcmp(t, "Text-delta")) {
				node_ctx.text_delta = !strcmp(val, "true");
				break;
			}
			if (constcmp(t, "Prop-delta"))
				continue;
			node_ctx.prop_delta = !strcmp(val, "true");
			break;
		case sizeof("Content-length"):
			if (constcmp(t, "Content-length"))
				continue;
			len = atoi(val);
			t = buffer_read_line(&input);
			if (!t)
				die_short_read();
			if (*t)
				die("invalid dump: expected blank line after content length header");
			if (active_ctx == REV_CTX) {
				read_props();
			} else if (active_ctx == NODE_CTX) {
				handle_node();
				active_ctx = INTERNODE_CTX;
			} else {
				fprintf(stderr, "Unexpected content length header: %"PRIu32"\n", len);
				if (buffer_skip_bytes(&input, len) != len)
					die_short_read();
			}
		}
	}
	if (buffer_ferror(&input))
		die_short_read();
	if (active_ctx == NODE_CTX)
		handle_node();
	if (active_ctx == REV_CTX)
		begin_revision(local_ref);
	if (active_ctx != DUMP_CTX)
		end_revision(notes_ref);
}