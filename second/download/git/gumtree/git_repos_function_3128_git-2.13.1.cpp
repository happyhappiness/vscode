static void range_set_move(struct range_set *dst, struct range_set *src)
{
	range_set_release(dst);
	dst->ranges = src->ranges;
	dst->nr = src->nr;
	dst->alloc = src->alloc;
	src->ranges = NULL;
	src->alloc = src->nr = 0;
}