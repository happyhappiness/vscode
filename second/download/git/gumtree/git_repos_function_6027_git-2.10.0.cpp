static void handle_property(const struct strbuf *key_buf,
				struct strbuf *val,
				uint32_t *type_set)
{
	const char *key = key_buf->buf;
	size_t keylen = key_buf->len;

	switch (keylen + 1) {
	case sizeof("svn:log"):
		if (constcmp(key, "svn:log"))
			break;
		if (!val)
			die("invalid dump: unsets svn:log");
		strbuf_swap(&rev_ctx.log, val);
		break;
	case sizeof("svn:author"):
		if (constcmp(key, "svn:author"))
			break;
		if (!val)
			strbuf_reset(&rev_ctx.author);
		else
			strbuf_swap(&rev_ctx.author, val);
		break;
	case sizeof("svn:date"):
		if (constcmp(key, "svn:date"))
			break;
		if (!val)
			die("invalid dump: unsets svn:date");
		if (parse_date_basic(val->buf, &rev_ctx.timestamp, NULL))
			warning("invalid timestamp: %s", val->buf);
		break;
	case sizeof("svn:executable"):
	case sizeof("svn:special"):
		if (keylen == strlen("svn:executable") &&
		    constcmp(key, "svn:executable"))
			break;
		if (keylen == strlen("svn:special") &&
		    constcmp(key, "svn:special"))
			break;
		if (*type_set) {
			if (!val)
				return;
			die("invalid dump: sets type twice");
		}
		if (!val) {
			node_ctx.type = REPO_MODE_BLB;
			return;
		}
		*type_set = 1;
		node_ctx.type = keylen == strlen("svn:executable") ?
				REPO_MODE_EXE :
				REPO_MODE_LNK;
	}
}