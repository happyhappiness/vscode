static struct commit_list *best_bisection_sorted(struct commit_list *list, int nr)
{
	struct commit_list *p;
	struct commit_dist *array = xcalloc(nr, sizeof(*array));
	struct strbuf buf = STRBUF_INIT;
	int cnt, i;

	for (p = list, cnt = 0; p; p = p->next) {
		int distance;
		unsigned flags = p->item->object.flags;

		if (flags & TREESAME)
			continue;
		distance = weight(p);
		if (nr - distance < distance)
			distance = nr - distance;
		array[cnt].commit = p->item;
		array[cnt].distance = distance;
		cnt++;
	}
	QSORT(array, cnt, compare_commit_dist);
	for (p = list, i = 0; i < cnt; i++) {
		struct object *obj = &(array[i].commit->object);

		strbuf_reset(&buf);
		strbuf_addf(&buf, "dist=%d", array[i].distance);
		add_name_decoration(DECORATION_NONE, buf.buf, obj);

		p->item = array[i].commit;
		p = p->next;
	}
	if (p)
		p->next = NULL;
	strbuf_release(&buf);
	free(array);
	return list;
}