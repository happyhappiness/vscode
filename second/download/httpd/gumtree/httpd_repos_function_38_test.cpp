void clear_commit_marks_for_object_array(struct object_array *a, unsigned mark)
{
	struct object *object;
	struct commit *commit;
	unsigned int i;

	for (i = 0; i < a->nr; i++) {
		object = a->objects[i].item;
		commit = lookup_commit_reference_gently(object->sha1, 1);
		if (commit)
			clear_commit_marks(commit, mark);
	}
}