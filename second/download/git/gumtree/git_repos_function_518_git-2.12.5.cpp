void pretty_print_ref(const char *name, const unsigned char *sha1,
		const char *format)
{
	struct ref_array_item *ref_item;
	ref_item = new_ref_array_item(name, sha1, 0);
	ref_item->kind = ref_kind_from_refname(name);
	show_ref_array_item(ref_item, format, 0);
	free_array_item(ref_item);
}