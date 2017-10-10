			die("cannot deflate request; zlib end error %d", ret);

		gzip_size = stream.total_out;

		headers = curl_slist_append(headers, "Content-Encoding: gzip");
		curl_easy_setopt(slot->curl, CURLOPT_POSTFIELDS, gzip_body);
		curl_easy_setopt(slot->curl, CURLOPT_POSTFIELDSIZE_LARGE, xcurl_off_t(gzip_size));

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
		curl_easy_setopt(slot->curl, CURLOPT_POSTFIELDSIZE_LARGE, xcurl_off_t(rpc->len));
		if (options.verbosity > 1) {
			fprintf(stderr, "POST %s (%lu bytes)\n",
				rpc->service_name, (unsigned long)rpc->len);
			fflush(stderr);
		}
	}
