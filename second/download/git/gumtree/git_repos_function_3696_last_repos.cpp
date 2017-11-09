static void handle(int incoming, struct sockaddr *addr, socklen_t addrlen)
{
	struct child_process cld = CHILD_PROCESS_INIT;

	if (max_connections && live_children >= max_connections) {
		kill_some_child();
		sleep(1);  /* give it some time to die */
		check_dead_children();
		if (live_children >= max_connections) {
			close(incoming);
			logerror("Too many children, dropping connection");
			return;
		}
	}

	if (addr->sa_family == AF_INET) {
		char buf[128] = "";
		struct sockaddr_in *sin_addr = (void *) addr;
		inet_ntop(addr->sa_family, &sin_addr->sin_addr, buf, sizeof(buf));
		argv_array_pushf(&cld.env_array, "REMOTE_ADDR=%s", buf);
		argv_array_pushf(&cld.env_array, "REMOTE_PORT=%d",
				 ntohs(sin_addr->sin_port));
#ifndef NO_IPV6
	} else if (addr->sa_family == AF_INET6) {
		char buf[128] = "";
		struct sockaddr_in6 *sin6_addr = (void *) addr;
		inet_ntop(AF_INET6, &sin6_addr->sin6_addr, buf, sizeof(buf));
		argv_array_pushf(&cld.env_array, "REMOTE_ADDR=[%s]", buf);
		argv_array_pushf(&cld.env_array, "REMOTE_PORT=%d",
				 ntohs(sin6_addr->sin6_port));
#endif
	}

	cld.argv = cld_argv.argv;
	cld.in = incoming;
	cld.out = dup(incoming);

	if (start_command(&cld))
		logerror("unable to fork");
	else
		add_child(&cld, addr, addrlen);
}