static struct commit *find_single_initial(struct rev_info *revs,
					  const char **name_p)
{
	int i;
	struct commit *found = NULL;
	const char *name = NULL;

	/*
	 * There must be one and only one negative commit, and it must be
	 * the boundary.
	 */
	for (i = 0; i < revs->pending.nr; i++) {
		struct object *obj = revs->pending.objects[i].item;
		if (!(obj->flags & UNINTERESTING))
			continue;
		obj = deref_tag(obj, NULL, 0);
		if (obj->type != OBJ_COMMIT)
			die("Non commit %s?", revs->pending.objects[i].name);
		if (found)
			die("More than one commit to dig up from, %s and %s?",
			    revs->pending.objects[i].name, name);
		found = (struct commit *) obj;
		name = revs->pending.objects[i].name;
	}

	if (!name)
		found = dwim_reverse_initial(revs, &name);
	if (!name)
		die("No commit to dig up from?");

	if (name_p)
		*name_p = xstrdup(name);
	return found;
}