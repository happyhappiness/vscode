void pretty_print_ref(const char *name, const unsigned char *sha1,
		      const struct ref_format *format)
{
	struct ref_array_item *ref_item;
	ref_item = new_ref_array_item(name, sha1, 0);
	ref_item->kind = ref_kind_from_refname(name);
	show_ref_array_item(ref_item, format);
	free_array_item(ref_item);
}