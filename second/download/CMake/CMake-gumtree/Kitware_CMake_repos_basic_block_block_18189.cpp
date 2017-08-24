{
	assert(pos >= FULL_DISTANCES);

	if (pos < fastpos_limit(FULL_DISTANCES_BITS - 1, 0))
		return fastpos_result(pos, FULL_DISTANCES_BITS - 1, 0);

	if (pos < fastpos_limit(FULL_DISTANCES_BITS - 1, 1))
		return fastpos_result(pos, FULL_DISTANCES_BITS - 1, 1);

	return fastpos_result(pos, FULL_DISTANCES_BITS - 1, 2);
}