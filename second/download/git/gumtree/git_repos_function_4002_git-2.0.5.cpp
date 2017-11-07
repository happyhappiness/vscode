static int handle_octopus(int count, const char **args, int show_all)
{
	struct commit_list *revs = NULL;
	struct commit_list *result;
	int i;

	for (i = count - 1; i >= 0; i--)
		commit_list_insert(get_commit_reference(args[i]), &revs);

	result = reduce_heads(get_octopus_merge_bases(revs));

	if (!result)
		return 1;

	while (result) {
		printf("%s\n", sha1_to_hex(result->item->object.sha1));
		if (!show_all)
			return 0;
		result = result->next;
	}

	return 0;
}