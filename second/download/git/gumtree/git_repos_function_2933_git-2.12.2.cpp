static void read_multi_file_filter_status(int fd, struct strbuf *status)
{
	struct strbuf **pair;
	char *line;
	for (;;) {
		line = packet_read_line(fd, NULL);
		if (!line)
			break;
		pair = strbuf_split_str(line, '=', 2);
		if (pair[0] && pair[0]->len && pair[1]) {
			/* the last "status=<foo>" line wins */
			if (!strcmp(pair[0]->buf, "status=")) {
				strbuf_reset(status);
				strbuf_addbuf(status, pair[1]);
			}
		}
		strbuf_list_free(pair);
	}
}