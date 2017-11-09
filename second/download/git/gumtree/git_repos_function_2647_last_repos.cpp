static int measure_abbrev(const struct object_id *oid, int sofar)
{
	char hex[GIT_MAX_HEXSZ + 1];
	int w = find_unique_abbrev_r(hex, oid->hash, DEFAULT_ABBREV);

	return (w < sofar) ? sofar : w;
}