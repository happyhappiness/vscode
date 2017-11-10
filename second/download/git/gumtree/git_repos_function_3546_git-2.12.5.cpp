static struct diff_filespec *filespec_from_entry(struct diff_filespec *target,
						 struct stage_data *entry,
						 int stage)
{
	struct object_id *oid = &entry->stages[stage].oid;
	unsigned mode = entry->stages[stage].mode;
	if (mode == 0 || is_null_oid(oid))
		return NULL;
	oidcpy(&target->oid, oid);
	target->mode = mode;
	return target;
}