void run_active_slot(struct active_request_slot *slot)
{
#ifdef USE_CURL_MULTI
	fd_set readfds;
	fd_set writefds;
	fd_set excfds;
	int max_fd;
	struct timeval select_timeout;
	int finished = 0;

	slot->finished = &finished;
	while (!finished) {
		step_active_slots();

		if (slot->in_use) {
#if LIBCURL_VERSION_NUM >= 0x070f04
			long curl_timeout;
			curl_multi_timeout(curlm, &curl_timeout);
			if (curl_timeout == 0) {
				continue;
			} else if (curl_timeout == -1) {
				select_timeout.tv_sec  = 0;
				select_timeout.tv_usec = 50000;
			} else {
				select_timeout.tv_sec  =  curl_timeout / 1000;
				select_timeout.tv_usec = (curl_timeout % 1000) * 1000;
			}
#else
			select_timeout.tv_sec  = 0;
			select_timeout.tv_usec = 50000;
#endif

			max_fd = -1;
			FD_ZERO(&readfds);
			FD_ZERO(&writefds);
			FD_ZERO(&excfds);
			curl_multi_fdset(curlm, &readfds, &writefds, &excfds, &max_fd);

			/*
			 * It can happen that curl_multi_timeout returns a pathologically
			 * long timeout when curl_multi_fdset returns no file descriptors
			 * to read.  See commit message for more details.
			 */
			if (max_fd < 0 &&
			    (select_timeout.tv_sec > 0 ||
			     select_timeout.tv_usec > 50000)) {
				select_timeout.tv_sec  = 0;
				select_timeout.tv_usec = 50000;
			}

			select(max_fd+1, &readfds, &writefds, &excfds, &select_timeout);
		}
	}
#else
	while (slot->in_use) {
		slot->curl_result = curl_easy_perform(slot->curl);
		finish_active_slot(slot);
	}
#endif
}