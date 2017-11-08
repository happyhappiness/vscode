static void cleanup_children(int sig, int in_signal)
{
	while (children_to_clean) {
		struct child_to_clean *p = children_to_clean;
		children_to_clean = p->next;
		kill(p->pid, sig);
		if (!in_signal)
			free(p);
	}
}