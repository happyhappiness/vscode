static void deepen(int depth, int deepen_relative,
		   struct object_array *shallows)
{
	if (depth == INFINITE_DEPTH && !is_repository_shallow()) {
		int i;

		for (i = 0; i < shallows->nr; i++) {
			struct object *object = shallows->objects[i].item;
			object->flags |= NOT_SHALLOW;
		}
	} else if (deepen_relative) {
		struct object_array reachable_shallows = OBJECT_ARRAY_INIT;
		struct commit_list *result;

		get_reachable_list(shallows, &reachable_shallows);
		result = get_shallow_commits(&reachable_shallows,
					     depth + 1,
					     SHALLOW, NOT_SHALLOW);
		send_shallow(result);
		free_commit_list(result);
		object_array_clear(&reachable_shallows);
	} else {
		struct commit_list *result;

		result = get_shallow_commits(&want_obj, depth,
					     SHALLOW, NOT_SHALLOW);
		send_shallow(result);
		free_commit_list(result);
	}

	send_unshallow(shallows);
	packet_flush(1);
}