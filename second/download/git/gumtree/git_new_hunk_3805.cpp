	ret = run_hook_ve(env, name, args);
	va_end(args);

	return ret;
}

struct io_pump {
	/* initialized by caller */
	int fd;
	int type; /* POLLOUT or POLLIN */
	union {
		struct {
			const char *buf;
			size_t len;
		} out;
		struct {
			struct strbuf *buf;
			size_t hint;
		} in;
	} u;

	/* returned by pump_io */
	int error; /* 0 for success, otherwise errno */

	/* internal use */
	struct pollfd *pfd;
};

static int pump_io_round(struct io_pump *slots, int nr, struct pollfd *pfd)
{
	int pollsize = 0;
	int i;

	for (i = 0; i < nr; i++) {
		struct io_pump *io = &slots[i];
		if (io->fd < 0)
			continue;
		pfd[pollsize].fd = io->fd;
		pfd[pollsize].events = io->type;
		io->pfd = &pfd[pollsize++];
	}

	if (!pollsize)
		return 0;

	if (poll(pfd, pollsize, -1) < 0) {
		if (errno == EINTR)
			return 1;
		die_errno("poll failed");
	}

	for (i = 0; i < nr; i++) {
		struct io_pump *io = &slots[i];

		if (io->fd < 0)
			continue;

		if (!(io->pfd->revents & (POLLOUT|POLLIN|POLLHUP|POLLERR|POLLNVAL)))
			continue;

		if (io->type == POLLOUT) {
			ssize_t len = xwrite(io->fd,
					     io->u.out.buf, io->u.out.len);
			if (len < 0) {
				io->error = errno;
				close(io->fd);
				io->fd = -1;
			} else {
				io->u.out.buf += len;
				io->u.out.len -= len;
				if (!io->u.out.len) {
					close(io->fd);
					io->fd = -1;
				}
			}
		}

		if (io->type == POLLIN) {
			ssize_t len = strbuf_read_once(io->u.in.buf,
						       io->fd, io->u.in.hint);
			if (len < 0)
				io->error = errno;
			if (len <= 0) {
				close(io->fd);
				io->fd = -1;
			}
		}
	}

	return 1;
}

static int pump_io(struct io_pump *slots, int nr)
{
	struct pollfd *pfd;
	int i;

	for (i = 0; i < nr; i++)
		slots[i].error = 0;

	ALLOC_ARRAY(pfd, nr);
	while (pump_io_round(slots, nr, pfd))
		; /* nothing */
	free(pfd);

	/* There may be multiple errno values, so just pick the first. */
	for (i = 0; i < nr; i++) {
		if (slots[i].error) {
			errno = slots[i].error;
			return -1;
		}
	}
	return 0;
}


int pipe_command(struct child_process *cmd,
		 const char *in, size_t in_len,
		 struct strbuf *out, size_t out_hint,
		 struct strbuf *err, size_t err_hint)
{
	struct io_pump io[3];
	int nr = 0;

	if (in)
		cmd->in = -1;
	if (out)
		cmd->out = -1;
	if (err)
		cmd->err = -1;

	if (start_command(cmd) < 0)
		return -1;

	if (in) {
		io[nr].fd = cmd->in;
		io[nr].type = POLLOUT;
		io[nr].u.out.buf = in;
		io[nr].u.out.len = in_len;
		nr++;
	}
	if (out) {
		io[nr].fd = cmd->out;
		io[nr].type = POLLIN;
		io[nr].u.in.buf = out;
		io[nr].u.in.hint = out_hint;
		nr++;
	}
	if (err) {
		io[nr].fd = cmd->err;
		io[nr].type = POLLIN;
		io[nr].u.in.buf = err;
		io[nr].u.in.hint = err_hint;
		nr++;
	}

	if (pump_io(io, nr) < 0) {
		finish_command(cmd); /* throw away exit code */
		return -1;
	}

	return finish_command(cmd);
}

enum child_state {
	GIT_CP_FREE,
	GIT_CP_WORKING,
