static struct commit *next_reflog_commit(struct commit_reflog *log)
{
	for (; log->recno >= 0; log->recno--) {
		struct reflog_info *entry = &log->reflogs->items[log->recno];
		struct object *obj = parse_object(&entry->noid);

		if (obj && obj->type == OBJ_COMMIT)
			return (struct commit *)obj;
	}
	return NULL;
}