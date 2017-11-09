static int delta_pos_compare(const void *_a, const void *_b)
{
	struct ref_delta_entry *a = *(struct ref_delta_entry **)_a;
	struct ref_delta_entry *b = *(struct ref_delta_entry **)_b;
	return a->obj_no - b->obj_no;
}