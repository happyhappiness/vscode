static void paint_down(struct paint_info *info, const struct object_id *oid,
		       unsigned int id)
{
	unsigned int i, nr;
	struct commit_list *head = NULL;
	int bitmap_nr = DIV_ROUND_UP(info->nr_bits, 32);
	size_t bitmap_size = st_mult(sizeof(uint32_t), bitmap_nr);
	struct commit *c = lookup_commit_reference_gently(oid, 1);
	uint32_t *tmp; /* to be freed before return */
	uint32_t *bitmap;

	if (!c)
		return;

	tmp = xmalloc(bitmap_size);
	bitmap = paint_alloc(info);
	memset(bitmap, 0, bitmap_size);
	bitmap[id / 32] |= (1U << (id % 32));
	commit_list_insert(c, &head);
	while (head) {
		struct commit_list *p;
		struct commit *c = pop_commit(&head);
		uint32_t **refs = ref_bitmap_at(&info->ref_bitmap, c);

		/* XXX check "UNINTERESTING" from pack bitmaps if available */
		if (c->object.flags & (SEEN | UNINTERESTING))
			continue;
		else
			c->object.flags |= SEEN;

		if (*refs == NULL)
			*refs = bitmap;
		else {
			memcpy(tmp, *refs, bitmap_size);
			for (i = 0; i < bitmap_nr; i++)
				tmp[i] |= bitmap[i];
			if (memcmp(tmp, *refs, bitmap_size)) {
				*refs = paint_alloc(info);
				memcpy(*refs, tmp, bitmap_size);
			}
		}

		if (c->object.flags & BOTTOM)
			continue;

		if (parse_commit(c))
			die("unable to parse commit %s",
			    oid_to_hex(&c->object.oid));

		for (p = c->parents; p; p = p->next) {
			if (p->item->object.flags & SEEN)
				continue;
			commit_list_insert(p->item, &head);
		}
	}

	nr = get_max_object_index();
	for (i = 0; i < nr; i++) {
		struct object *o = get_indexed_object(i);
		if (o && o->type == OBJ_COMMIT)
			o->flags &= ~SEEN;
	}

	free(tmp);
}