int cmd_upload_archive(int argc, const char **argv, const char *prefix)
{
	struct child_process writer = { argv };

	/*
	 * Set up sideband subprocess.
	 *
	 * We (parent) monitor and read from child, sending its fd#1 and fd#2
	 * multiplexed out to our fd#1.  If the child dies, we tell the other
	 * end over channel #3.
	 */
	argv[0] = "upload-archive--writer";
	writer.out = writer.err = -1;
	writer.git_cmd = 1;
	if (start_command(&writer)) {
		int err = errno;
		packet_write(1, "NACK unable to spawn subprocess\n");
		die("upload-archive: %s", strerror(err));
	}

	packet_write(1, "ACK\n");
	packet_flush(1);

	while (1) {
		struct pollfd pfd[2];

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
			if (process_input(pfd[1].fd, 2))
				continue;
		if (pfd[0].revents & POLLIN)
			/* Data stream ready */
			if (process_input(pfd[0].fd, 1))
				continue;

		if (finish_command(&writer))
			error_clnt("%s", deadchild);
		packet_flush(1);
		break;
	}
	return 0;
}