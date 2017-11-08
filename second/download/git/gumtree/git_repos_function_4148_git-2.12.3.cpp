int ref_compare_name(const void *va, const void *vb)
{
	const struct ref *a = va, *b = vb;
	return strcmp(a->name, b->name);
}