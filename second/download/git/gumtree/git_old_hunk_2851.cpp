
	result = reduce_heads(revs);
	if (!result)
		return 1;

	while (result) {
		printf("%s\n", sha1_to_hex(result->item->object.sha1));
		result = result->next;
	}
	return 0;
}

static int handle_octopus(int count, const char **args, int show_all)
