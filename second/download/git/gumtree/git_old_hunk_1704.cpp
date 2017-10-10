
	printf("\n");

	show_progress();
}

static void handle_tail(struct object_array *commits, struct rev_info *revs)
{
	struct commit *commit;
	while (commits->nr) {
		commit = (struct commit *)commits->objects[commits->nr - 1].item;
		if (has_unshown_parent(commit))
