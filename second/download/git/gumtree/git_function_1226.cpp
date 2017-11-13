static struct commit *find_single_final(struct rev_info *revs,
					const char **name_p)
{
	int i;
	struct commit *found = NULL;
	const char *name = NULL;

	for (i = 0; i < revs->pending.nr; i++) {
		struct object *obj = revs->pending.objects[i].item;
		if (obj->flags & UNINTERESTING)
			continue;
		obj = deref_tag(obj, NULL, 0);
		if (obj->type != OBJ_COMMIT)
			die("Non commit %s?", revs->pending.objects[i].name);
		if (found)
			die("More than one commit to dig from %s and %s?",
			    revs->pending.objects[i].name, name);
		found = (struct commit *)obj;
		name = revs->pending.objects[i].name;
	}
	if (name_p)
		*name_p = name;
	return found;
}