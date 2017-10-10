}

static struct command **queue_command(struct command **tail,
				      const char *line,
				      int linelen)
{
	struct object_id old_oid, new_oid;
	struct command *cmd;
	const char *refname;
	int reflen;
	const char *p;

	if (parse_oid_hex(line, &old_oid, &p) ||
	    *p++ != ' ' ||
	    parse_oid_hex(p, &new_oid, &p) ||
	    *p++ != ' ')
		die("protocol error: expected old/new/ref, got '%s'", line);

	refname = p;
	reflen = linelen - (p - line);
	FLEX_ALLOC_MEM(cmd, ref_name, refname, reflen);
	oidcpy(&cmd->old_oid, &old_oid);
	oidcpy(&cmd->new_oid, &new_oid);
	*tail = cmd;
	return &cmd->next;
}

static void queue_commands_from_cert(struct command **tail,
				     struct strbuf *push_cert)
