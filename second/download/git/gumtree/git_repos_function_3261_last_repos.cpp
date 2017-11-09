void range_set_release(struct range_set *rs)
{
	FREE_AND_NULL(rs->ranges);
	rs->alloc = rs->nr = 0;
}