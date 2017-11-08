static int read_one_reflog(unsigned char *osha1, unsigned char *nsha1,
		const char *email, unsigned long timestamp, int tz,
		const char *message, void *cb_data)
{
	struct complete_reflogs *array = cb_data;
	struct reflog_info *item;

	ALLOC_GROW(array->items, array->nr + 1, array->alloc);
	item = array->items + array->nr;
	hashcpy(item->osha1, osha1);
	hashcpy(item->nsha1, nsha1);
	item->email = xstrdup(email);
	item->timestamp = timestamp;
	item->tz = tz;
	item->message = xstrdup(message);
	array->nr++;
	return 0;
}