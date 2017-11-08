static int read_bisect_refs(void)
{
	return for_each_ref_in("refs/bisect/", register_ref, NULL);
}