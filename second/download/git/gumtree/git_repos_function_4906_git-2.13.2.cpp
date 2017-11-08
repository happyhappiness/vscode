static void show_suffix(int depth, const struct object_id *oid)
{
	printf("-%d-g%s", depth, find_unique_abbrev(oid->hash, abbrev));
}