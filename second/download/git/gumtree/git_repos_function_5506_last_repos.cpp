static void check_connectivity(void)
{
	int i, max;

	/* Traverse the pending reachable objects */
	traverse_reachable();

	/* Look up all the requirements, warn about missing objects.. */
	max = get_max_object_index();
	if (verbose)
		fprintf(stderr, "Checking connectivity (%d objects)\n", max);

	for (i = 0; i < max; i++) {
		struct object *obj = get_indexed_object(i);

		if (obj)
			check_object(obj);
	}
}