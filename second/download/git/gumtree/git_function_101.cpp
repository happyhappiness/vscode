static void update_refs_stdin(void)
{
	struct strbuf cmd = STRBUF_INIT;

	/* Read each line dispatch its command */
	while (strbuf_getline(&cmd, stdin, line_termination) != EOF)
		if (!cmd.buf[0])
			die("empty command in input");
		else if (isspace(*cmd.buf))
			die("whitespace before command: %s", cmd.buf);
		else if (starts_with(cmd.buf, "update "))
			parse_cmd_update(cmd.buf + 7);
		else if (starts_with(cmd.buf, "create "))
			parse_cmd_create(cmd.buf + 7);
		else if (starts_with(cmd.buf, "delete "))
			parse_cmd_delete(cmd.buf + 7);
		else if (starts_with(cmd.buf, "verify "))
			parse_cmd_verify(cmd.buf + 7);
		else if (starts_with(cmd.buf, "option "))
			parse_cmd_option(cmd.buf + 7);
		else
			die("unknown command: %s", cmd.buf);

	strbuf_release(&cmd);
}