static int curl_append_msgs_to_imap(struct imap_server_conf *server,
				    struct strbuf* all_msgs, int total) {
	int ofs = 0;
	int n = 0;
	struct buffer msgbuf = { STRBUF_INIT, 0 };
	CURL *curl;
	CURLcode res = CURLE_OK;

	curl = setup_curl(server);
	curl_easy_setopt(curl, CURLOPT_READDATA, &msgbuf);

	fprintf(stderr, "sending %d message%s\n", total, (total != 1) ? "s" : "");
	while (1) {
		unsigned percent = n * 100 / total;
		int prev_len;

		fprintf(stderr, "%4u%% (%d/%d) done\r", percent, n, total);

		prev_len = msgbuf.buf.len;
		if (!split_msg(all_msgs, &msgbuf.buf, &ofs))
			break;
		if (server->use_html)
			wrap_in_html(&msgbuf.buf);
		lf_to_crlf(&msgbuf.buf);

		curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE,
				 (curl_off_t)(msgbuf.buf.len-prev_len));

		res = curl_easy_perform(curl);

		if(res != CURLE_OK) {
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
					curl_easy_strerror(res));
			break;
		}

		n++;
	}
	fprintf(stderr, "\n");

	curl_easy_cleanup(curl);
	curl_global_cleanup();

	return 0;
}