static struct object_entry *find_object(struct object_id *oid)
{
	unsigned int h = oid->hash[0] << 8 | oid->hash[1];
	struct object_entry *e;
	for (e = object_table[h]; e; e = e->next)
		if (!oidcmp(oid, &e->idx.oid))
			return e;
	return NULL;
}