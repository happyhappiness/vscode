void kill_all(int sig)
{
	int i;

	for (i = 0; i < num_pids; i++) {
		/* Let's just be a little careful where we
		 * point that gun, hey?  See kill(2) for the
		 * magic caused by negative values. */
		pid_t p = all_pids[i];

		if (p == getpid())
			continue;
		if (p <= 0)
			continue;

		kill(p, sig);
	}
}