void range_set_release(struct range_set *rs)
{
	free(rs->ranges);
	rs->alloc = rs->nr = 0;
	rs->ranges = NULL;
}