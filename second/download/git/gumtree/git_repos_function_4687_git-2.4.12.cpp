static int compare_delta_bases(const union delta_base *base1,
			       const union delta_base *base2,
			       enum object_type type1,
			       enum object_type type2)
{
	int cmp = type1 - type2;
	if (cmp)
		return cmp;
	return memcmp(base1, base2, UNION_BASE_SZ);
}