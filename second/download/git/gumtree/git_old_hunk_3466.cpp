		return 0;	/* No space for more. */

	transfer_debug("%s is readable", t->src_name);
	bytes = read(t->src, t->buf + t->bufuse, BUFFERSIZE - t->bufuse);
	if (bytes < 0 && errno != EWOULDBLOCK && errno != EAGAIN &&
		errno != EINTR) {
		error("read(%s) failed: %s", t->src_name, strerror(errno));
		return -1;
	} else if (bytes == 0) {
		transfer_debug("%s EOF (with %i bytes in buffer)",
			t->src_name, (int)t->bufuse);
		t->state = SSTATE_FLUSHING;
	} else if (bytes > 0) {
