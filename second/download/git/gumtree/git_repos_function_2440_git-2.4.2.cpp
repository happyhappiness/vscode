static void range_set_union(struct range_set *out,
			     struct range_set *a, struct range_set *b)
{
	int i = 0, j = 0, o = 0;
	struct range *ra = a->ranges;
	struct range *rb = b->ranges;
	/* cannot make an alias of out->ranges: it may change during grow */

	assert(out->nr == 0);
	while (i < a->nr || j < b->nr) {
		struct range *new;
		if (i < a->nr && j < b->nr) {
			if (ra[i].start < rb[j].start)
				new = &ra[i++];
			else if (ra[i].start > rb[j].start)
				new = &rb[j++];
			else if (ra[i].end < rb[j].end)
				new = &ra[i++];
			else
				new = &rb[j++];
		} else if (i < a->nr)      /* b exhausted */
			new = &ra[i++];
		else                       /* a exhausted */
			new = &rb[j++];
		if (new->start == new->end)
			; /* empty range */
		else if (!o || out->ranges[o-1].end < new->start) {
			range_set_grow(out, 1);
			out->ranges[o].start = new->start;
			out->ranges[o].end = new->end;
			o++;
		} else if (out->ranges[o-1].end < new->end) {
			out->ranges[o-1].end = new->end;
		}
	}
	out->nr = o;
}