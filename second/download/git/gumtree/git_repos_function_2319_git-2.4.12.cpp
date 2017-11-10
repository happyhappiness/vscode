static int post_rpc(struct rpc_state *rpc)
{
	struct active_request_slot *slot;
	struct curl_slist *headers = NULL;
	int use_gzip = rpc->gzip_request;
	char *gzip_body = NULL;
	size_t gzip_size = 0;
	int err, large_request = 0;
	int needs_100_continue = 0;

	/* Try to load the entire request, if we can fit it into the
	 * allocated buffer space we can use HTTP/1.0 and avoid the
	 * chunked encoding mess.
	 */
	while (1) {
		size_t left = rpc->alloc - rpc->len;
		char *buf = rpc->buf + rpc->len;
		int n;

		if (left < LARGE_PACKET_MAX) {
			large_request = 1;
			use_gzip = 0;
			break;
		}

		n = packet_read(rpc->out, NULL, NULL, buf, left, 0);
		if (!n)
			break;
		rpc->len += n;
	}

	if (large_request) {
		struct slot_results results;

		do {
			err = probe_rpc(rpc, &results);
			if (err == HTTP_REAUTH)
				credential_fill(&http_auth);
		} while (err == HTTP_REAUTH);
		if (err != HTTP_OK)
			return -1;

		if (results.auth_avail & CURLAUTH_GSSNEGOTIATE)
			needs_100_continue = 1;
	}

	headers = curl_slist_append(headers, rpc->hdr_content_type);
	headers = curl_slist_append(headers, rpc->hdr_accept);
	headers = curl_slist_append(headers, needs_100_continue ?
		"Expect: 100-continue" : "Expect:");

retry:
	slot = get_active_slot();

	curl_easy_setopt(slot->curl, CURLOPT_NOBODY, 0);
	curl_easy_setopt(slot->curl, CURLOPT_POST, 1);
	curl_easy_setopt(slot->curl, CURLOPT_URL, rpc->service_url);
	curl_easy_setopt(slot->curl, CURLOPT_ENCODING, "gzip");

	if (large_request) {
		/* The request body is large and the size cannot be predicted.
		 * We must use chunked encoding to send it.
		 */
		headers = curl_slist_append(headers, "Transfer-Encoding: chunked");
		rpc->initial_buffer = 1;
		curl_easy_setopt(slot->curl, CURLOPT_READFUNCTION, rpc_out);
		curl_easy_setopt(slot->curl, CURLOPT_INFILE, rpc);
#ifndef NO_CURL_IOCTL
		curl_easy_setopt(slot->curl, CURLOPT_IOCTLFUNCTION, rpc_ioctl);
		curl_easy_setopt(slot->curl, CURLOPT_IOCTLDATA, rpc);
#endif
		if (options.verbosity > 1) {
			fprintf(stderr, "POST %s (chunked)\n", rpc->service_name);
			fflush(stderr);
		}

	} else if (gzip_body) {
		/*
		 * If we are looping to retry authentication, then the previous
		 * run will have set up the headers and gzip buffer already,
		 * and we just need to send it.
		 */
		curl_easy_setopt(slot->curl, CURLOPT_POSTFIELDS, gzip_body);
		curl_easy_setopt(slot->curl, CURLOPT_POSTFIELDSIZE, gzip_size);

	} else if (use_gzip && 1024 < rpc->len) {
		/* The client backend isn't giving us compressed data so
		 * we can try to deflate it ourselves, this may save on.
		 * the transfer time.
		 */
		git_zstream stream;
		int ret;

		git_deflate_init_gzip(&stream, Z_BEST_COMPRESSION);
		gzip_size = git_deflate_bound(&stream, rpc->len);
		gzip_body = xmalloc(gzip_size);

		stream.next_in = (unsigned char *)rpc->buf;
		stream.avail_in = rpc->len;
		stream.next_out = (unsigned char *)gzip_body;
		stream.avail_out = gzip_size;

		ret = git_deflate(&stream, Z_FINISH);
		if (ret != Z_STREAM_END)
			die("cannot deflate request; zlib deflate error %d", ret);

		ret = git_deflate_end_gently(&stream);
		if (ret != Z_OK)
			die("cannot deflate request; zlib end error %d", ret);

		gzip_size = stream.total_out;

		headers = curl_slist_append(headers, "Content-Encoding: gzip");
		curl_easy_setopt(slot->curl, CURLOPT_POSTFIELDS, gzip_body);
		curl_easy_setopt(slot->curl, CURLOPT_POSTFIELDSIZE, gzip_size);

		if (options.verbosity > 1) {
			fprintf(stderr, "POST %s (gzip %lu to %lu bytes)\n",
				rpc->service_name,
				(unsigned long)rpc->len, (unsigned long)gzip_size);
			fflush(stderr);
		}
	} else {
		/* We know the complete request size in advance, use the
		 * more normal Content-Length approach.
		 */
		curl_easy_setopt(slot->curl, CURLOPT_POSTFIELDS, rpc->buf);
		curl_easy_setopt(slot->curl, CURLOPT_POSTFIELDSIZE, rpc->len);
		if (options.verbosity > 1) {
			fprintf(stderr, "POST %s (%lu bytes)\n",
				rpc->service_name, (unsigned long)rpc->len);
			fflush(stderr);
		}
	}

	curl_easy_setopt(slot->curl, CURLOPT_HTTPHEADER, headers);
	curl_easy_setopt(slot->curl, CURLOPT_WRITEFUNCTION, rpc_in);
	curl_easy_setopt(slot->curl, CURLOPT_FILE, rpc);

	err = run_slot(slot, NULL);
	if (err == HTTP_REAUTH && !large_request) {
		credential_fill(&http_auth);
		goto retry;
	}
	if (err != HTTP_OK)
		err = -1;

	curl_slist_free_all(headers);
	free(gzip_body);
	return err;
}