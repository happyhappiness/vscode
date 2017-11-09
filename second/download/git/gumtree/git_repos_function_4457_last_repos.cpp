static struct ref *make_linked_ref(const char *name, struct ref ***tail)
{
	struct ref *ret = alloc_ref(name);
	tail_link_ref(ret, tail);
	return ret;
}