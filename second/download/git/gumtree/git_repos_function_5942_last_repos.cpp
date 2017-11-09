static void handle_tags_and_duplicates(void)
{
	struct commit *commit;
	int i;

	for (i = extra_refs.nr - 1; i >= 0; i--) {
		const char *name = extra_refs.items[i].string;
		struct object *object = extra_refs.items[i].util;
		switch (object->type) {
		case OBJ_TAG:
			handle_tag(name, (struct tag *)object);
			break;
		case OBJ_COMMIT:
			if (anonymize)
				name = anonymize_refname(name);
			/* create refs pointing to already seen commits */
			commit = (struct commit *)object;
			printf("reset %s\nfrom :%d\n\n", name,
			       get_object_mark(&commit->object));
			show_progress();
			break;
		}
	}
}