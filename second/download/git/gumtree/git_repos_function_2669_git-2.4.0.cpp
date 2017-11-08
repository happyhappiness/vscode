static int ref_update_compare(const void *r1, const void *r2)
{
	const struct ref_update * const *u1 = r1;
	const struct ref_update * const *u2 = r2;
	return strcmp((*u1)->refname, (*u2)->refname);
}