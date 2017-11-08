static const char *dwim_reverse_initial(struct scoreboard *sb)
{
	/*
	 * DWIM "git blame --reverse ONE -- PATH" as
	 * "git blame --reverse ONE..HEAD -- PATH" but only do so
	 * when it makes sense.
	 */
	struct object *obj;
	struct commit *head_commit;
	unsigned char head_sha1[20];

	if (sb->revs->pending.nr != 1)
		return NULL;

	/* Is that sole rev a committish? */
	obj = sb->revs->pending.objects[0].item;
	obj = deref_tag(obj, NULL, 0);
	if (obj->type != OBJ_COMMIT)
		return NULL;

	/* Do we have HEAD? */
	if (!resolve_ref_unsafe("HEAD", RESOLVE_REF_READING, head_sha1, NULL))
		return NULL;
	head_commit = lookup_commit_reference_gently(head_sha1, 1);
	if (!head_commit)
		return NULL;

	/* Turn "ONE" into "ONE..HEAD" then */
	obj->flags |= UNINTERESTING;
	add_pending_object(sb->revs, &head_commit->object, "HEAD");

	sb->final = (struct commit *)obj;
	return sb->revs->pending.objects[0].name;
}