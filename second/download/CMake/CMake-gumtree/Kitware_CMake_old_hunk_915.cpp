	tree_push(t, base, t->full_path.s, 0, 0, 0, NULL);

	archive_wstring_free(&ws);

	t->stack->flags = needsFirstVisit;

	return (t);

failed:

	archive_wstring_free(&ws);

