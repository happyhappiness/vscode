static void paint_down(struct paint_info *info, const unsigned char *sha1,
		       int id)
{
	unsigned int i, nr;
	struct commit_list *head = NULL;
	int bitmap_nr = (info->nr_bits + 31) / 32;
	int bitmap_size = bitmap_nr * sizeof(uint32_t);
	uint32_t *tmp = xmalloc(bitmap_size); /* to be freed before return */
	uint32_t *bitmap = paint_alloc(info);
	struct commit *c = lookup_commit_reference_gently(sha1, 1);
	if (!c)
		return;
	memset(bitmap, 0, bitmap_size);
	bitmap[id / 32] |= (1 << (id % 32));
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
			    sha1_to_hex(c->object.sha1));

		for (p = c->parents; p; p = p->next) {
			uint32_t **p_refs = ref_bitmap_at(&info->ref_bitmap,
							  p->item);
			if (p->item->object.flags & SEEN)
				continue;
			if (*p_refs == NULL || *p_refs == *refs)
				*p_refs = *refs;
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