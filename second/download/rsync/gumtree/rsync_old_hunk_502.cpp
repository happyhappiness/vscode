	return rsync_module(fd, i);
}


int daemon_main(void)
{
	if (is_a_socket(STDIN_FILENO)) {
		/* we are running via inetd */
		return start_daemon(STDIN_FILENO);
	}

	become_daemon();

	start_accept_loop(rsync_port, start_daemon);
	return -1;
}

