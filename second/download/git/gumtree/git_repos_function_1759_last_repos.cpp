static struct object_entry *insert_object(struct object_id *oid)
{
	unsigned int h = oid->hash[0] << 8 | oid->hash[1];
	struct object_entry *e = object_table[h];

	while (e) {
		if (!oidcmp(oid, &e->idx.oid))
			return e;
		e = e->next;
	}

	e = new_object(oid);
	e->next = object_table[h];
	e->idx.offset = 0;
	object_table[h] = e;
	return e;
}