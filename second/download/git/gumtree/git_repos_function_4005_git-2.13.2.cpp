static int compare_objs_order(const void *a_, const void *b_)
{
	struct obj_order const *a, *b;
	a = (struct obj_order const *)a_;
	b = (struct obj_order const *)b_;
	if (a->order != b->order)
		return a->order - b->order;
	return a->orig_order - b->orig_order;
}