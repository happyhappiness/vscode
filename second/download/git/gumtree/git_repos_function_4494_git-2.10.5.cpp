static char *prepare_initial(struct scoreboard *sb)
{
	int i;
	const char *final_commit_name = NULL;
	struct rev_info *revs = sb->revs;

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
		if (sb->final)
			die("More than one commit to dig down to %s and %s?",
			    revs->pending.objects[i].name,
			    final_commit_name);
		sb->final = (struct commit *) obj;
		final_commit_name = revs->pending.objects[i].name;
	}
	if (!final_commit_name)
		die("No commit to dig down to?");
	return xstrdup(final_commit_name);
}