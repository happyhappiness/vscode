static struct commit *dwim_reverse_initial(struct rev_info *revs,
					   const char **name_p)
{
	/*
	 * DWIM "git blame --reverse ONE -- PATH" as
	 * "git blame --reverse ONE..HEAD -- PATH" but only do so
	 * when it makes sense.
	 */
	struct object *obj;
	struct commit *head_commit;
	struct object_id head_oid;

	if (revs->pending.nr != 1)
		return NULL;

	/* Is that sole rev a committish? */
	obj = revs->pending.objects[0].item;
	obj = deref_tag(obj, NULL, 0);
	if (obj->type != OBJ_COMMIT)
		return NULL;

	/* Do we have HEAD? */
	if (!resolve_ref_unsafe("HEAD", RESOLVE_REF_READING, head_oid.hash, NULL))
		return NULL;
	head_commit = lookup_commit_reference_gently(&head_oid, 1);
	if (!head_commit)
		return NULL;

	/* Turn "ONE" into "ONE..HEAD" then */
	obj->flags |= UNINTERESTING;
	add_pending_object(revs, &head_commit->object, "HEAD");

	if (name_p)
		*name_p = revs->pending.objects[0].name;
	return (struct commit *)obj;
}