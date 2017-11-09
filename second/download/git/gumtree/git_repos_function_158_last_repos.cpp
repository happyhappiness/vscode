static void deepen_by_rev_list(int ac, const char **av,
			       struct object_array *shallows)
{
	struct commit_list *result;

	result = get_shallow_commits_by_rev_list(ac, av, SHALLOW, NOT_SHALLOW);
	send_shallow(result);
	free_commit_list(result);
	send_unshallow(shallows);
	packet_flush(1);
}