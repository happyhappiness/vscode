static int generate_info_refs(FILE *fp)
{
	return for_each_ref(add_info_ref, fp);
}