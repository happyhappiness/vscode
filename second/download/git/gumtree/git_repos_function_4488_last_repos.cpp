int ref_newer(const struct object_id *new_oid, const struct object_id *old_oid)
{
	struct object *o;
	struct commit *old, *new;
	struct commit_list *list, *used;
	int found = 0;

	/*
	 * Both new and old must be commit-ish and new is descendant of
	 * old.  Otherwise we require --force.
	 */
	o = deref_tag(parse_object(old_oid), NULL, 0);
	if (!o || o->type != OBJ_COMMIT)
		return 0;
	old = (struct commit *) o;

	o = deref_tag(parse_object(new_oid), NULL, 0);
	if (!o || o->type != OBJ_COMMIT)
		return 0;
	new = (struct commit *) o;

	if (parse_commit(new) < 0)
		return 0;

	used = list = NULL;
	commit_list_insert(new, &list);
	while (list) {
		new = pop_most_recent_commit(&list, TMP_MARK);
		commit_list_insert(new, &used);
		if (new == old) {
			found = 1;
			break;
		}
	}
	unmark_and_free(list, TMP_MARK);
	unmark_and_free(used, TMP_MARK);
	return found;
}