static void cleanup_children(int sig, int in_signal)
{
	struct child_to_clean *children_to_wait_for = NULL;

	while (children_to_clean) {
		struct child_to_clean *p = children_to_clean;
		children_to_clean = p->next;

		if (p->process && !in_signal) {
			struct child_process *process = p->process;
			if (process->clean_on_exit_handler) {
				trace_printf(
					"trace: run_command: running exit handler for pid %"
					PRIuMAX, (uintmax_t)p->pid
				);
				process->clean_on_exit_handler(process);
			}
		}

		kill(p->pid, sig);

		if (p->process && p->process->wait_after_clean) {
			p->next = children_to_wait_for;
			children_to_wait_for = p;
		} else {
			if (!in_signal)
				free(p);
		}
	}

	while (children_to_wait_for) {
		struct child_to_clean *p = children_to_wait_for;
		children_to_wait_for = p->next;

		while (waitpid(p->pid, NULL, 0) < 0 && errno == EINTR)
			; /* spin waiting for process exit or error */

		if (!in_signal)
			free(p);
	}
}