			 opt->subject_prefix);
		subject = buffer;
	} else {
		subject = "Subject: ";
	}

	printf("From %s Mon Sep 17 00:00:00 2001\n", name);
	graph_show_oneline(opt->graph);
	if (opt->message_id) {
		printf("Message-Id: <%s>\n", opt->message_id);
		graph_show_oneline(opt->graph);
	}
	if (opt->ref_message_ids && opt->ref_message_ids->nr > 0) {
		int i, n;
		n = opt->ref_message_ids->nr;
		printf("In-Reply-To: <%s>\n", opt->ref_message_ids->items[n-1].string);
		for (i = 0; i < n; i++)
			printf("%s<%s>\n", (i > 0 ? "\t" : "References: "),
			       opt->ref_message_ids->items[i].string);
		graph_show_oneline(opt->graph);
	}
	if (opt->mime_boundary) {
		static char subject_buffer[1024];
		static char buffer[1024];
