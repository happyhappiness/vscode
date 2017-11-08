int resolve_remote_symref(struct ref *ref, struct ref *list)
{
	if (!ref->symref)
		return 0;
	for (; list; list = list->next)
		if (!strcmp(ref->symref, list->name)) {
			oidcpy(&ref->old_oid, &list->old_oid);
			return 0;
		}
	return 1;
}