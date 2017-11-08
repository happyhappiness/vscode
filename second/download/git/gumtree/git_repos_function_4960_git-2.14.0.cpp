static void create_reflog_msg(const struct object_id *oid, struct strbuf *sb)
{
	enum object_type type;
	struct commit *c;
	char *buf;
	unsigned long size;
	int subject_len = 0;
	const char *subject_start;

	char *rla = getenv("GIT_REFLOG_ACTION");
	if (rla) {
		strbuf_addstr(sb, rla);
	} else {
		strbuf_addstr(sb, "tag: tagging ");
		strbuf_add_unique_abbrev(sb, oid->hash, DEFAULT_ABBREV);
	}

	strbuf_addstr(sb, " (");
	type = sha1_object_info(oid->hash, NULL);
	switch (type) {
	default:
		strbuf_addstr(sb, "object of unknown type");
		break;
	case OBJ_COMMIT:
		if ((buf = read_sha1_file(oid->hash, &type, &size)) != NULL) {
			subject_len = find_commit_subject(buf, &subject_start);
			strbuf_insert(sb, sb->len, subject_start, subject_len);
		} else {
			strbuf_addstr(sb, "commit object");
		}
		free(buf);

		if ((c = lookup_commit_reference(oid)) != NULL)
			strbuf_addf(sb, ", %s", show_date(c->date, 0, DATE_MODE(SHORT)));
		break;
	case OBJ_TREE:
		strbuf_addstr(sb, "tree object");
		break;
	case OBJ_BLOB:
		strbuf_addstr(sb, "blob object");
		break;
	case OBJ_TAG:
		strbuf_addstr(sb, "other tag object");
		break;
	}
	strbuf_addch(sb, ')');
}