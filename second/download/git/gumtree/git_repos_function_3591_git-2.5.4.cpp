int resolve_remote_symref(struct ref *ref, struct ref *list)
{
	if (!ref->symref)
		return 0;
	for (; list; list = list->next)
		if (!strcmp(ref->symref, list->name)) {
			hashcpy(ref->old_sha1, list->old_sha1);
			return 0;
		}
	return 1;
}