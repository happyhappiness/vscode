static void range_set_copy(struct range_set *dst, struct range_set *src)
{
	range_set_init(dst, src->nr);
	COPY_ARRAY(dst->ranges, src->ranges, src->nr);
	dst->nr = src->nr;
}