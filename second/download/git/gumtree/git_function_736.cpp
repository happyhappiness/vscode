static int receive_unpack_status(int in)
{
	const char *line = packet_read_line(in, NULL);
	if (!skip_prefix(line, "unpack ", &line))
		return error(_("unable to parse remote unpack status: %s"), line);
	if (strcmp(line, "ok"))
		return error(_("remote unpack failed: %s"), line);
	return 0;
}