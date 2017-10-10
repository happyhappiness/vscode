		return -1;
	}

	close(cmd->out);
	return finish_command(cmd);
}

enum child_state {
	GIT_CP_FREE,
	GIT_CP_WORKING,
	GIT_CP_WAIT_CLEANUP,
};

struct parallel_processes {
	void *data;

	int max_processes;
	int nr_processes;

	get_next_task_fn get_next_task;
	start_failure_fn start_failure;
	task_finished_fn task_finished;

	struct {
		enum child_state state;
		struct child_process process;
		struct strbuf err;
		void *data;
	} *children;
	/*
	 * The struct pollfd is logically part of *children,
	 * but the system call expects it as its own array.
	 */
	struct pollfd *pfd;

	unsigned shutdown : 1;

	int output_owner;
	struct strbuf buffered_output; /* of finished children */
};

static int default_start_failure(struct strbuf *err,
				 void *pp_cb,
				 void *pp_task_cb)
{
	return 0;
}

static int default_task_finished(int result,
				 struct strbuf *err,
				 void *pp_cb,
				 void *pp_task_cb)
{
	return 0;
}

static void kill_children(struct parallel_processes *pp, int signo)
{
	int i, n = pp->max_processes;

	for (i = 0; i < n; i++)
		if (pp->children[i].state == GIT_CP_WORKING)
			kill(pp->children[i].process.pid, signo);
}

static struct parallel_processes *pp_for_signal;

static void handle_children_on_signal(int signo)
{
	kill_children(pp_for_signal, signo);
	sigchain_pop(signo);
	raise(signo);
}

static void pp_init(struct parallel_processes *pp,
		    int n,
		    get_next_task_fn get_next_task,
		    start_failure_fn start_failure,
		    task_finished_fn task_finished,
		    void *data)
{
	int i;

	if (n < 1)
		n = online_cpus();

	pp->max_processes = n;

	trace_printf("run_processes_parallel: preparing to run up to %d tasks", n);

	pp->data = data;
	if (!get_next_task)
		die("BUG: you need to specify a get_next_task function");
	pp->get_next_task = get_next_task;

	pp->start_failure = start_failure ? start_failure : default_start_failure;
	pp->task_finished = task_finished ? task_finished : default_task_finished;

	pp->nr_processes = 0;
	pp->output_owner = 0;
	pp->shutdown = 0;
	pp->children = xcalloc(n, sizeof(*pp->children));
	pp->pfd = xcalloc(n, sizeof(*pp->pfd));
	strbuf_init(&pp->buffered_output, 0);

	for (i = 0; i < n; i++) {
		strbuf_init(&pp->children[i].err, 0);
		child_process_init(&pp->children[i].process);
		pp->pfd[i].events = POLLIN | POLLHUP;
		pp->pfd[i].fd = -1;
	}

	pp_for_signal = pp;
	sigchain_push_common(handle_children_on_signal);
}

static void pp_cleanup(struct parallel_processes *pp)
{
	int i;

	trace_printf("run_processes_parallel: done");
	for (i = 0; i < pp->max_processes; i++) {
		strbuf_release(&pp->children[i].err);
		child_process_clear(&pp->children[i].process);
	}

	free(pp->children);
	free(pp->pfd);

	/*
	 * When get_next_task added messages to the buffer in its last
	 * iteration, the buffered output is non empty.
	 */
	fputs(pp->buffered_output.buf, stderr);
	strbuf_release(&pp->buffered_output);

	sigchain_pop_common();
}

/* returns
 *  0 if a new task was started.
 *  1 if no new jobs was started (get_next_task ran out of work, non critical
 *    problem with starting a new command)
 * <0 no new job was started, user wishes to shutdown early. Use negative code
 *    to signal the children.
 */
static int pp_start_one(struct parallel_processes *pp)
{
	int i, code;

	for (i = 0; i < pp->max_processes; i++)
		if (pp->children[i].state == GIT_CP_FREE)
			break;
	if (i == pp->max_processes)
		die("BUG: bookkeeping is hard");

	code = pp->get_next_task(&pp->children[i].process,
				 &pp->children[i].err,
				 pp->data,
				 &pp->children[i].data);
	if (!code) {
		strbuf_addbuf(&pp->buffered_output, &pp->children[i].err);
		strbuf_reset(&pp->children[i].err);
		return 1;
	}
	pp->children[i].process.err = -1;
	pp->children[i].process.stdout_to_stderr = 1;
	pp->children[i].process.no_stdin = 1;

	if (start_command(&pp->children[i].process)) {
		code = pp->start_failure(&pp->children[i].err,
					 pp->data,
					 &pp->children[i].data);
		strbuf_addbuf(&pp->buffered_output, &pp->children[i].err);
		strbuf_reset(&pp->children[i].err);
		if (code)
			pp->shutdown = 1;
		return code;
	}

	pp->nr_processes++;
	pp->children[i].state = GIT_CP_WORKING;
	pp->pfd[i].fd = pp->children[i].process.err;
	return 0;
}

static void pp_buffer_stderr(struct parallel_processes *pp, int output_timeout)
{
	int i;

	while ((i = poll(pp->pfd, pp->max_processes, output_timeout)) < 0) {
		if (errno == EINTR)
			continue;
		pp_cleanup(pp);
		die_errno("poll");
	}

	/* Buffer output from all pipes. */
	for (i = 0; i < pp->max_processes; i++) {
		if (pp->children[i].state == GIT_CP_WORKING &&
		    pp->pfd[i].revents & (POLLIN | POLLHUP)) {
			int n = strbuf_read_once(&pp->children[i].err,
						 pp->children[i].process.err, 0);
			if (n == 0) {
				close(pp->children[i].process.err);
				pp->children[i].state = GIT_CP_WAIT_CLEANUP;
			} else if (n < 0)
				if (errno != EAGAIN)
					die_errno("read");
		}
	}
}

static void pp_output(struct parallel_processes *pp)
{
	int i = pp->output_owner;
	if (pp->children[i].state == GIT_CP_WORKING &&
	    pp->children[i].err.len) {
		fputs(pp->children[i].err.buf, stderr);
		strbuf_reset(&pp->children[i].err);
	}
}

static int pp_collect_finished(struct parallel_processes *pp)
{
	int i, code;
	int n = pp->max_processes;
	int result = 0;

	while (pp->nr_processes > 0) {
		for (i = 0; i < pp->max_processes; i++)
			if (pp->children[i].state == GIT_CP_WAIT_CLEANUP)
				break;
		if (i == pp->max_processes)
			break;

		code = finish_command(&pp->children[i].process);

		code = pp->task_finished(code,
					 &pp->children[i].err, pp->data,
					 &pp->children[i].data);

		if (code)
			result = code;
		if (code < 0)
			break;

		pp->nr_processes--;
		pp->children[i].state = GIT_CP_FREE;
		pp->pfd[i].fd = -1;
		child_process_init(&pp->children[i].process);

		if (i != pp->output_owner) {
			strbuf_addbuf(&pp->buffered_output, &pp->children[i].err);
			strbuf_reset(&pp->children[i].err);
		} else {
			fputs(pp->children[i].err.buf, stderr);
			strbuf_reset(&pp->children[i].err);

			/* Output all other finished child processes */
			fputs(pp->buffered_output.buf, stderr);
			strbuf_reset(&pp->buffered_output);

			/*
			 * Pick next process to output live.
			 * NEEDSWORK:
			 * For now we pick it randomly by doing a round
			 * robin. Later we may want to pick the one with
			 * the most output or the longest or shortest
			 * running process time.
			 */
			for (i = 0; i < n; i++)
				if (pp->children[(pp->output_owner + i) % n].state == GIT_CP_WORKING)
					break;
			pp->output_owner = (pp->output_owner + i) % n;
		}
	}
	return result;
}

int run_processes_parallel(int n,
			   get_next_task_fn get_next_task,
			   start_failure_fn start_failure,
			   task_finished_fn task_finished,
			   void *pp_cb)
{
	int i, code;
	int output_timeout = 100;
	int spawn_cap = 4;
	struct parallel_processes pp;

	pp_init(&pp, n, get_next_task, start_failure, task_finished, pp_cb);
	while (1) {
		for (i = 0;
		    i < spawn_cap && !pp.shutdown &&
		    pp.nr_processes < pp.max_processes;
		    i++) {
			code = pp_start_one(&pp);
			if (!code)
				continue;
			if (code < 0) {
				pp.shutdown = 1;
				kill_children(&pp, -code);
			}
			break;
		}
		if (!pp.nr_processes)
			break;
		pp_buffer_stderr(&pp, output_timeout);
		pp_output(&pp);
		code = pp_collect_finished(&pp);
		if (code) {
			pp.shutdown = 1;
			if (code < 0)
				kill_children(&pp, -code);
		}
	}

	pp_cleanup(&pp);
	return 0;
}
