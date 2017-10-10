
	if (is_repository_shallow())
		write_shallow_commits(&req_buf, 1, NULL);
	if (args->depth > 0)
		packet_buf_write(&req_buf, "deepen %d", args->depth);
	if (args->deepen_since) {
		timestamp_t max_age = approxidate(args->deepen_since);
		packet_buf_write(&req_buf, "deepen-since %"PRItime, max_age);
	}
	if (args->deepen_not) {
		int i;
		for (i = 0; i < args->deepen_not->nr; i++) {
			struct string_list_item *s = args->deepen_not->items + i;
			packet_buf_write(&req_buf, "deepen-not %s", s->string);
