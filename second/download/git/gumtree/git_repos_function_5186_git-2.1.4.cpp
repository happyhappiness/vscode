static void update_refs_stdin(void)
{
	struct strbuf input = STRBUF_INIT;
	const char *next;

	if (strbuf_read(&input, 0, 1000) < 0)
		die_errno("could not read from stdin");
	next = input.buf;
	/* Read each line dispatch its command */
	while (next < input.buf + input.len) {
		if (*next == line_termination)
			die("empty command in input");
		else if (isspace(*next))
			die("whitespace before command: %s", next);
		else if (starts_with(next, "update "))
			next = parse_cmd_update(&input, next + 7);
		else if (starts_with(next, "create "))
			next = parse_cmd_create(&input, next + 7);
		else if (starts_with(next, "delete "))
			next = parse_cmd_delete(&input, next + 7);
		else if (starts_with(next, "verify "))
			next = parse_cmd_verify(&input, next + 7);
		else if (starts_with(next, "option "))
			next = parse_cmd_option(&input, next + 7);
		else
			die("unknown command: %s", next);

		next++;
	}

	strbuf_release(&input);
}