static void range_set_copy(struct range_set *dst, struct range_set *src)
{
	range_set_init(dst, src->nr);
	memcpy(dst->ranges, src->ranges, src->nr*sizeof(struct range_set));
	dst->nr = src->nr;
}