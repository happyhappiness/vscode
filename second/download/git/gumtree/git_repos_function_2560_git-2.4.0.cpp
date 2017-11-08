static int entry_matches(struct ref_entry *entry, const struct string_list *list)
{
	return list && string_list_has_string(list, entry->name);
}