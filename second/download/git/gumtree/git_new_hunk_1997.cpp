	if (!total) {
		fprintf(stderr, "no messages to send\n");
		return 1;
	}

	/* write it to the imap server */

	if (server.tunnel)
		return append_msgs_to_imap(&server, &all_msgs, total);

#ifdef USE_CURL_FOR_IMAP_SEND
	if (use_curl)
		return curl_append_msgs_to_imap(&server, &all_msgs, total);
#endif

	return append_msgs_to_imap(&server, &all_msgs, total);
}
