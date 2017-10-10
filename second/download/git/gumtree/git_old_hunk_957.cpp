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
	FLEX_ALLOC_MEM(cmd, ref_name, refname, reflen);
	hashcpy(cmd->old_sha1, old_sha1);
	hashcpy(cmd->new_sha1, new_sha1);
	*tail = cmd;
	return &cmd->next;
}

static void queue_commands_from_cert(struct command **tail,
				     struct strbuf *push_cert)
