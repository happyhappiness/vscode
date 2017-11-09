static int fall_back_to_classic_diff(struct hashmap *map,
		int line1, int count1, int line2, int count2)
{
	xpparam_t xpp;
	xpp.flags = map->xpp->flags & ~XDF_DIFF_ALGORITHM_MASK;

	return xdl_fall_back_diff(map->env, &xpp,
				  line1, count1, line2, count2);
}