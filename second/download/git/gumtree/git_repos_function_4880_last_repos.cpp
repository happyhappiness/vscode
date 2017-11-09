static int match(struct hashmap *map, int line1, int line2)
{
	xrecord_t *record1 = map->env->xdf1.recs[line1 - 1];
	xrecord_t *record2 = map->env->xdf2.recs[line2 - 1];
	return xdl_recmatch(record1->ptr, record1->size,
		record2->ptr, record2->size, map->xpp->flags);
}