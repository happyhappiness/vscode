static void lookup_credential(const struct string_list *fns, struct credential *c)
{
	struct string_list_item *fn;

	for_each_string_list_item(fn, fns)
		if (parse_credential_file(fn->string, c, print_entry, NULL))
			return; /* Found credential */
}