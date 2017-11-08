static const char *get_parameter(const char *name)
{
	struct string_list_item *i;
	i = string_list_lookup(get_parameters(), name);
	return i ? i->util : NULL;
}