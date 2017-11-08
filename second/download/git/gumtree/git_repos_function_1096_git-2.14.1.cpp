static int stash_count_refs(struct object_id *ooid, struct object_id *noid,
			    const char *email, timestamp_t timestamp, int tz,
			    const char *message, void *cb_data)
{
	int *c = cb_data;
	(*c)++;
	return 0;
}