		(*count)++;
		read_next_command();
	}
	return list;
}

static void parse_new_commit(void)
{
	static struct strbuf msg = STRBUF_INIT;
	struct branch *b;
	char *sp;
	char *author = NULL;
	char *committer = NULL;
	struct hash_list *merge_list = NULL;
	unsigned int merge_count;
	unsigned char prev_fanout, new_fanout;

	/* Obtain the branch name from the rest of our command */
	sp = strchr(command_buf.buf, ' ') + 1;
	b = lookup_branch(sp);
	if (!b)
		b = new_branch(sp);

	read_next_command();
	parse_mark();
	if (starts_with(command_buf.buf, "author ")) {
		author = parse_ident(command_buf.buf + 7);
		read_next_command();
	}
	if (starts_with(command_buf.buf, "committer ")) {
		committer = parse_ident(command_buf.buf + 10);
		read_next_command();
	}
	if (!committer)
		die("Expected committer but didn't get one");
	parse_data(&msg, 0, NULL);
	read_next_command();
