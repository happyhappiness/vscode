static int service_loop(struct socketlist *socklist)
{
	struct pollfd *pfd;
	int i;

	pfd = xcalloc(socklist->nr, sizeof(struct pollfd));

	for (i = 0; i < socklist->nr; i++) {
		pfd[i].fd = socklist->list[i];
		pfd[i].events = POLLIN;
	}

	signal(SIGCHLD, child_handler);

	for (;;) {
		int i;

		check_dead_children();

		if (poll(pfd, socklist->nr, -1) < 0) {
			if (errno != EINTR) {
				logerror("Poll failed, resuming: %s",
				      strerror(errno));
				sleep(1);
			}
			continue;
		}

		for (i = 0; i < socklist->nr; i++) {
			if (pfd[i].revents & POLLIN) {
				union {
					struct sockaddr sa;
					struct sockaddr_in sai;
#ifndef NO_IPV6
					struct sockaddr_in6 sai6;
#endif
				} ss;
				socklen_t sslen = sizeof(ss);
				int incoming = accept(pfd[i].fd, &ss.sa, &sslen);
				if (incoming < 0) {
					switch (errno) {
					case EAGAIN:
					case EINTR:
					case ECONNABORTED:
						continue;
					default:
						die_errno("accept returned");
					}
				}
				handle(incoming, &ss.sa, sslen);
			}
		}
	}
}