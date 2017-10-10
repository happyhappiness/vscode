		pfd[0].fd = writer.out;
		pfd[0].events = POLLIN;
		pfd[1].fd = writer.err;
		pfd[1].events = POLLIN;
		if (poll(pfd, 2, -1) < 0) {
			if (errno != EINTR) {
				error_errno("poll failed resuming");
				sleep(1);
			}
			continue;
		}
		if (pfd[1].revents & POLLIN)
			/* Status stream ready */
