struct ref *alloc_ref(const char *name)
{
	return alloc_ref_with_prefix("", 0, name);
}