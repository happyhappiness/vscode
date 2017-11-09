static void kill_children(struct parallel_processes *pp, int signo)
{
	int i, n = pp->max_processes;

	for (i = 0; i < n; i++)
		if (pp->children[i].state == GIT_CP_WORKING)
			kill(pp->children[i].process.pid, signo);
}