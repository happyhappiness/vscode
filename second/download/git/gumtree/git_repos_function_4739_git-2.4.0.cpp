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
	cmd = xcalloc(1, sizeof(struct command) + reflen + 1);
	hashcpy(cmd->old_sha1, old_sha1);
	hashcpy(cmd->new_sha1, new_sha1);
	memcpy(cmd->ref_name, refname, reflen);
	cmd->ref_name[reflen] = '\0';
	*tail = cmd;
	return &cmd->next;
}