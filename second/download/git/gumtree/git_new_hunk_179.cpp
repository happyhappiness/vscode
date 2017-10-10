
	if (!store_object(OBJ_COMMIT, &new_data, NULL, b->sha1, next_mark))
		b->pack_id = pack_id;
	b->last_commit = object_count_by_type[OBJ_COMMIT];
}

static void parse_new_tag(const char *arg)
{
	static struct strbuf msg = STRBUF_INIT;
	const char *from;
	char *tagger;
	struct branch *s;
	struct tag *t;
	uintmax_t from_mark = 0;
	unsigned char sha1[20];
	enum object_type type;
	const char *v;

	t = pool_alloc(sizeof(struct tag));
	memset(t, 0, sizeof(struct tag));
	t->name = pool_strdup(arg);
	if (last_tag)
		last_tag->next_tag = t;
	else
		first_tag = t;
	last_tag = t;
	read_next_command();

	/* from ... */
	if (!skip_prefix(command_buf.buf, "from ", &from))
		die("Expected from command, got %s", command_buf.buf);
	s = lookup_branch(from);
	if (s) {
		if (is_null_sha1(s->sha1))
			die("Can't tag an empty branch.");
		hashcpy(sha1, s->sha1);
		type = OBJ_COMMIT;
