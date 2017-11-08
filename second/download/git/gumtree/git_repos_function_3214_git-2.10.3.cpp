static int oid_eq(const struct object_id *a, const struct object_id *b)
{
	if (!a && !b)
		return 2;
	return a && b && oidcmp(a, b) == 0;
}