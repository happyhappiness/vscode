		}
		free(buf);
		close(po.out);
		po.out = -1;
	}

	if (finish_command(&po))
		return -1;
	return 0;
}

static int receive_status(int in, struct ref *refs)
{
	struct ref *hint;
	int ret = 0;
	char *line = packet_read_line(in, NULL);
	if (!starts_with(line, "unpack "))
		return error("did not receive remote status");
	if (strcmp(line, "unpack ok")) {
		error("unpack failed: %s", line + 7);
		ret = -1;
	}
	hint = NULL;
	while (1) {
		char *refname;
		char *msg;
		line = packet_read_line(in, NULL);
		if (!line)
			break;
		if (!starts_with(line, "ok ") && !starts_with(line, "ng ")) {
			error("invalid ref status from remote: %s", line);
			ret = -1;
			break;
