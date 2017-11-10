static int read_one_reflog(struct object_id *ooid, struct object_id *noid,
		const char *email, unsigned long timestamp, int tz,
		const char *message, void *cb_data)
{
	struct complete_reflogs *array = cb_data;
	struct reflog_info *item;

	ALLOC_GROW(array->items, array->nr + 1, array->alloc);
	item = array->items + array->nr;
	oidcpy(&item->ooid, ooid);
	oidcpy(&item->noid, noid);
	item->email = xstrdup(email);
	item->timestamp = timestamp;
	item->tz = tz;
	item->message = xstrdup(message);
	array->nr++;
	return 0;
}