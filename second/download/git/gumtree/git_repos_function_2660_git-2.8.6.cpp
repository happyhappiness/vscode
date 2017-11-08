static struct spanhash_top *spanhash_rehash(struct spanhash_top *orig)
{
	struct spanhash_top *new;
	int i;
	int osz = 1 << orig->alloc_log2;
	int sz = osz << 1;

	new = xmalloc(st_add(sizeof(*orig),
			     st_mult(sizeof(struct spanhash), sz)));
	new->alloc_log2 = orig->alloc_log2 + 1;
	new->free = INITIAL_FREE(new->alloc_log2);
	memset(new->data, 0, sizeof(struct spanhash) * sz);
	for (i = 0; i < osz; i++) {
		struct spanhash *o = &(orig->data[i]);
		int bucket;
		if (!o->cnt)
			continue;
		bucket = o->hashval & (sz - 1);
		while (1) {
			struct spanhash *h = &(new->data[bucket++]);
			if (!h->cnt) {
				h->hashval = o->hashval;
				h->cnt = o->cnt;
				new->free--;
				break;
			}
			if (sz <= bucket)
				bucket = 0;
		}
	}
	free(orig);
	return new;
}