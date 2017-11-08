static void check_dead_children(void)
{
	int status;
	pid_t pid;

	struct child **cradle, *blanket;
	for (cradle = &firstborn; (blanket = *cradle);)
		if ((pid = waitpid(blanket->cld.pid, &status, WNOHANG)) > 1) {
			const char *dead = "";
			if (status)
				dead = " (with error)";
			loginfo("[%"PRIuMAX"] Disconnected%s", (uintmax_t)pid, dead);

			/* remove the child */
			*cradle = blanket->next;
			live_children--;
			child_process_clear(&blanket->cld);
			free(blanket);
		} else
			cradle = &blanket->next;
}