		(*count)++;
		read_next_command();
	}
	return list;
}

static void parse_new_commit(const char *arg)
{
	static struct strbuf msg = STRBUF_INIT;
	struct branch *b;
	char *author = NULL;
	char *committer = NULL;
	struct hash_list *merge_list = NULL;
	unsigned int merge_count;
	unsigned char prev_fanout, new_fanout;
	const char *v;

	b = lookup_branch(arg);
	if (!b)
		b = new_branch(arg);

	read_next_command();
	parse_mark();
	if (skip_prefix(command_buf.buf, "author ", &v)) {
		author = parse_ident(v);
		read_next_command();
	}
	if (skip_prefix(command_buf.buf, "committer ", &v)) {
		committer = parse_ident(v);
		read_next_command();
	}
	if (!committer)
		die("Expected committer but didn't get one");
	parse_data(&msg, 0, NULL);
	read_next_command();
