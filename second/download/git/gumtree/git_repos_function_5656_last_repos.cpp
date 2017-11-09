static void read_push_options(struct string_list *options)
{
	while (1) {
		char *line;
		int len;

		line = packet_read_line(0, &len);

		if (!line)
			break;

		string_list_append(options, line);
	}
}